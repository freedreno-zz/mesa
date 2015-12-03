/*
 * Copyright © 2014 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "brw_nir.h"
#include "brw_shader.h"
#include "glsl/nir/glsl_to_nir.h"
#include "glsl/nir/nir_builder.h"
#include "program/prog_to_nir.h"

struct remap_vs_attrs_state {
   nir_builder b;
   GLbitfield64 inputs_read;
};

static bool
remap_vs_attrs(nir_block *block, void *closure)
{
   struct remap_vs_attrs_state *state = closure;

   nir_foreach_instr_safe(block, instr) {
      if (instr->type != nir_instr_type_intrinsic)
         continue;

      nir_intrinsic_instr *intrin = nir_instr_as_intrinsic(instr);

      state->b.cursor = nir_before_instr(&intrin->instr);

      if (intrin->intrinsic == nir_intrinsic_load_input) {
         /* Attributes come in a contiguous block, ordered by their
          * gl_vert_attrib value.  That means we can compute the slot
          * number for an attribute by masking out the enabled attributes
          * before it and counting the bits.
          */
         nir_const_value *const_attr = nir_src_as_const_value(intrin->src[0]);

         /* We set EmitNoIndirect for VS inputs, so there are no indirects. */
         assert(const_attr != NULL);

         int attr = const_attr->u[0];
         int slot = _mesa_bitcount_64(state->inputs_read & BITFIELD64_MASK(attr));
         nir_instr_rewrite_src(&intrin->instr, &intrin->src[0],
                               nir_src_for_ssa(nir_imm_int(&state->b, 4 * slot)));
      }
   }
   return true;
}

static void
brw_nir_lower_inputs(nir_shader *nir,
                     const struct brw_device_info *devinfo,
                     bool is_scalar)
{
   switch (nir->stage) {
   case MESA_SHADER_VERTEX:
      /* Start with the location of the variable's base. */
      foreach_list_typed(nir_variable, var, node, &nir->inputs) {
         var->data.driver_location = var->data.location;
      }

      /* Now use nir_lower_io to walk dereference chains.  Attribute arrays
       * are loaded as one vec4 per element (or matrix column), so we use
       * type_size_vec4 here.
       */
      nir_lower_io(nir, nir_var_shader_in, type_size_vec4);

      if (is_scalar) {
         /* Finally, translate VERT_ATTRIB_* values into the actual registers.
          *
          * Note that we can use nir->info.inputs_read instead of
          * key->inputs_read since the two are identical aside from Gen4-5
          * edge flag differences.
          */

         /* This pass needs actual constants */
         nir_opt_constant_folding(nir);

         struct remap_vs_attrs_state state = {
            .inputs_read = nir->info.inputs_read
         };
         nir_foreach_overload(nir, overload) {
            if (overload->impl) {
               nir_builder_init(&state.b, overload->impl);
               nir_foreach_block(overload->impl, remap_vs_attrs, &state);
            }
         }
      }
      break;
   case MESA_SHADER_GEOMETRY: {
      if (!is_scalar) {
         foreach_list_typed(nir_variable, var, node, &nir->inputs) {
            var->data.driver_location = var->data.location;
         }
      } else {
         /* The GLSL linker will have already matched up GS inputs and
          * the outputs of prior stages.  The driver does extend VS outputs
          * in some cases, but only for legacy OpenGL or Gen4-5 hardware,
          * neither of which offer geometry shader support.  So we can
          * safely ignore that.
          *
          * For SSO pipelines, we use a fixed VUE map layout based on variable
          * locations, so we can rely on rendezvous-by-location to make this
          * work.
          *
          * However, we need to ignore VARYING_SLOT_PRIMITIVE_ID, as it's not
          * written by previous stages and shows up via payload magic.
          */
         struct brw_vue_map input_vue_map;
         GLbitfield64 inputs_read =
            nir->info.inputs_read & ~VARYING_BIT_PRIMITIVE_ID;
         brw_compute_vue_map(devinfo, &input_vue_map, inputs_read,
                             nir->info.separate_shader);

         /* Start with the slot for the variable's base. */
         foreach_list_typed(nir_variable, var, node, &nir->inputs) {
            assert(input_vue_map.varying_to_slot[var->data.location] != -1);
            var->data.driver_location =
               input_vue_map.varying_to_slot[var->data.location];
         }

         /* Inputs are stored in vec4 slots, so use type_size_vec4(). */
         nir_lower_io(nir, nir_var_shader_in, type_size_vec4);
      }
      break;
   }
   case MESA_SHADER_FRAGMENT:
      assert(is_scalar);
      nir_assign_var_locations(&nir->inputs, &nir->num_inputs,
                               type_size_scalar);
      break;
   case MESA_SHADER_COMPUTE:
      /* Compute shaders have no inputs. */
      assert(exec_list_is_empty(&nir->inputs));
      break;
   default:
      unreachable("unsupported shader stage");
   }
}

static void
brw_nir_lower_outputs(nir_shader *nir, bool is_scalar)
{
   switch (nir->stage) {
   case MESA_SHADER_VERTEX:
   case MESA_SHADER_GEOMETRY:
      if (is_scalar) {
         nir_assign_var_locations(&nir->outputs, &nir->num_outputs,
                                  type_size_vec4_times_4);
         nir_lower_io(nir, nir_var_shader_out, type_size_vec4_times_4);
      } else {
         nir_foreach_variable(var, &nir->outputs)
            var->data.driver_location = var->data.location;
      }
      break;
   case MESA_SHADER_FRAGMENT:
      nir_assign_var_locations(&nir->outputs, &nir->num_outputs,
                               type_size_scalar);
      break;
   case MESA_SHADER_COMPUTE:
      /* Compute shaders have no outputs. */
      assert(exec_list_is_empty(&nir->outputs));
      break;
   default:
      unreachable("unsupported shader stage");
   }
}

#include "util/debug.h"

static bool
should_clone_nir()
{
   static int should_clone = -1;
   if (should_clone < 1)
      should_clone = env_var_as_boolean("NIR_TEST_CLONE", false);

   return should_clone;
}

#define _OPT(do_pass) (({                                            \
   bool this_progress = true;                                        \
   do_pass                                                           \
   nir_validate_shader(nir);                                         \
   if (should_clone_nir()) {                                         \
      nir_shader *clone = nir_shader_clone(ralloc_parent(nir), nir); \
      ralloc_free(nir);                                              \
      nir = clone;                                                   \
   }                                                                 \
   this_progress;                                                    \
}))

#define OPT(pass, ...) _OPT(                   \
   nir_metadata_set_validation_flag(nir);      \
   this_progress = pass(nir ,##__VA_ARGS__);   \
   if (this_progress) {                        \
      progress = true;                         \
      nir_metadata_check_validation_flag(nir); \
   }                                           \
)

#define OPT_V(pass, ...) _OPT( \
   pass(nir, ##__VA_ARGS__);   \
)

static nir_shader *
nir_optimize(nir_shader *nir, bool is_scalar)
{
   bool progress;
   do {
      progress = false;
      OPT_V(nir_lower_vars_to_ssa);

      if (is_scalar) {
         OPT_V(nir_lower_alu_to_scalar);
      }

      OPT(nir_copy_prop);

      if (is_scalar) {
         OPT_V(nir_lower_phis_to_scalar);
      }

      OPT(nir_copy_prop);
      OPT(nir_opt_dce);
      OPT(nir_opt_cse);
      OPT(nir_opt_peephole_select);
      OPT(nir_opt_algebraic);
      OPT(nir_opt_constant_folding);
      OPT(nir_opt_dead_cf);
      OPT(nir_opt_remove_phis);
      OPT(nir_opt_undef);
   } while (progress);

   return nir;
}

/* Does some simple lowering and runs the standard suite of optimizations
 *
 * This is intended to be called more-or-less directly after you get the
 * shader out of GLSL or some other source.  While it is geared towards i965,
 * it is not at all generator-specific except for the is_scalar flag.  Even
 * there, it is safe to call with is_scalar = false for a shader that is
 * intended for the FS backend as long as nir_optimize is called again with
 * is_scalar = true to scalarize everything prior to code gen.
 */
nir_shader *
brw_preprocess_nir(nir_shader *nir, bool is_scalar)
{
   bool progress; /* Written by OPT and OPT_V */
   (void)progress;

   if (nir->stage == MESA_SHADER_GEOMETRY)
      OPT(nir_lower_gs_intrinsics);

   static const nir_lower_tex_options tex_options = {
      .lower_txp = ~0,
   };

   OPT(nir_lower_tex, &tex_options);
   OPT(nir_normalize_cubemap_coords);

   OPT(nir_lower_global_vars_to_local);

   OPT(nir_split_var_copies);

   nir = nir_optimize(nir, is_scalar);

   /* Lower a bunch of stuff */
   OPT_V(nir_lower_var_copies);

   /* Get rid of split copies */
   nir = nir_optimize(nir, is_scalar);

   OPT(nir_remove_dead_variables);

   return nir;
}

/* Lowers inputs, outputs, uniforms, and samplers for i965
 *
 * This function does all of the standard lowering prior to post-processing.
 * The lowering done is highly gen, stage, and backend-specific.  The
 * shader_prog parameter is optional and is used only for lowering sampler
 * derefs and atomics for GLSL shaders.
 */
nir_shader *
brw_lower_nir(nir_shader *nir,
              const struct brw_device_info *devinfo,
              const struct gl_shader_program *shader_prog,
              bool is_scalar)
{
   bool progress; /* Written by OPT and OPT_V */
   (void)progress;

   OPT_V(brw_nir_lower_inputs, devinfo, is_scalar);
   OPT_V(brw_nir_lower_outputs, is_scalar);
   nir_assign_var_locations(&nir->uniforms,
                            &nir->num_uniforms,
                            is_scalar ? type_size_scalar : type_size_vec4);
   OPT_V(nir_lower_io, nir_var_all, is_scalar ? type_size_scalar : type_size_vec4);

   if (shader_prog) {
      OPT_V(nir_lower_samplers, shader_prog);
   }

   OPT(nir_lower_system_values);

   if (shader_prog) {
      OPT_V(nir_lower_atomics, shader_prog);
   }

   return nir_optimize(nir, is_scalar);
}

/* Prepare the given shader for codegen
 *
 * This function is intended to be called right before going into the actual
 * backend and is highly backend-specific.  Also, once this function has been
 * called on a shader, it will no longer be in SSA form so most optimizations
 * will not work.
 */
nir_shader *
brw_postprocess_nir(nir_shader *nir,
                    const struct brw_device_info *devinfo,
                    bool is_scalar)
{
   bool debug_enabled =
      (INTEL_DEBUG & intel_debug_flag_for_shader_stage(nir->stage));

   bool progress; /* Written by OPT and OPT_V */
   (void)progress;

   if (devinfo->gen >= 6) {
      /* Try and fuse multiply-adds */
      OPT(brw_nir_opt_peephole_ffma);
   }

   OPT(nir_opt_algebraic_late);

   OPT(nir_lower_locals_to_regs);

   OPT_V(nir_lower_to_source_mods);
   OPT(nir_copy_prop);
   OPT(nir_opt_dce);

   if (unlikely(debug_enabled)) {
      /* Re-index SSA defs so we print more sensible numbers. */
      nir_foreach_overload(nir, overload) {
         if (overload->impl)
            nir_index_ssa_defs(overload->impl);
      }

      fprintf(stderr, "NIR (SSA form) for %s shader:\n",
              _mesa_shader_stage_to_string(nir->stage));
      nir_print_shader(nir, stderr);
   }

   OPT_V(nir_convert_from_ssa, true);

   if (!is_scalar) {
      OPT_V(nir_move_vec_src_uses_to_dest);
      OPT(nir_lower_vec_to_movs);
   }

   /* This is the last pass we run before we start emitting stuff.  It
    * determines when we need to insert boolean resolves on Gen <= 5.  We
    * run it last because it stashes data in instr->pass_flags and we don't
    * want that to be squashed by other NIR passes.
    */
   if (devinfo->gen <= 5)
      brw_nir_analyze_boolean_resolves(nir);

   nir_sweep(nir);

   if (unlikely(debug_enabled)) {
      fprintf(stderr, "NIR (final form) for %s shader:\n",
              _mesa_shader_stage_to_string(nir->stage));
      nir_print_shader(nir, stderr);
   }

   return nir;
}

nir_shader *
brw_create_nir(struct brw_context *brw,
               const struct gl_shader_program *shader_prog,
               const struct gl_program *prog,
               gl_shader_stage stage,
               bool is_scalar)
{
   struct gl_context *ctx = &brw->ctx;
   const struct brw_device_info *devinfo = brw->intelScreen->devinfo;
   const nir_shader_compiler_options *options =
      ctx->Const.ShaderCompilerOptions[stage].NirOptions;
   bool progress;
   nir_shader *nir;

   /* First, lower the GLSL IR or Mesa IR to NIR */
   if (shader_prog) {
      nir = glsl_to_nir(shader_prog, stage, options);
   } else {
      nir = prog_to_nir(prog, options);
      OPT_V(nir_convert_to_ssa); /* turn registers into SSA */
   }
   nir_validate_shader(nir);

   (void)progress;

   nir = brw_preprocess_nir(nir, is_scalar);
   nir = brw_lower_nir(nir, devinfo, shader_prog, is_scalar);

   return nir;
}

nir_shader *
brw_nir_apply_sampler_key(nir_shader *nir,
                          const struct brw_device_info *devinfo,
                          const struct brw_sampler_prog_key_data *key_tex,
                          bool is_scalar)
{
   nir_lower_tex_options tex_options = { 0 };

   /* Iron Lake and prior require lowering of all rectangle textures */
   if (devinfo->gen < 6)
      tex_options.lower_rect = true;

   /* Prior to Broadwell, our hardware can't actually do GL_CLAMP */
   if (devinfo->gen < 8) {
      tex_options.saturate_s = key_tex->gl_clamp_mask[0];
      tex_options.saturate_t = key_tex->gl_clamp_mask[1];
      tex_options.saturate_r = key_tex->gl_clamp_mask[2];
   }

   /* Prior to Haswell, we have to fake texture swizzle */
   for (unsigned s = 0; s < MAX_SAMPLERS; s++) {
      if (key_tex->swizzles[s] == SWIZZLE_NOOP)
         continue;

      tex_options.swizzle_result |= (1 << s);
      for (unsigned c = 0; c < 4; c++)
         tex_options.swizzles[s][c] = GET_SWZ(key_tex->swizzles[s], c);
   }

   if (nir_lower_tex(nir, &tex_options)) {
      nir_validate_shader(nir);
      nir = nir_optimize(nir, is_scalar);
   }

   return nir;
}

enum brw_reg_type
brw_type_for_nir_type(nir_alu_type type)
{
   switch (type) {
   case nir_type_uint:
      return BRW_REGISTER_TYPE_UD;
   case nir_type_bool:
   case nir_type_int:
      return BRW_REGISTER_TYPE_D;
   case nir_type_float:
      return BRW_REGISTER_TYPE_F;
   default:
      unreachable("unknown type");
   }

   return BRW_REGISTER_TYPE_F;
}

/* Returns the glsl_base_type corresponding to a nir_alu_type.
 * This is used by both brw_vec4_nir and brw_fs_nir.
 */
enum glsl_base_type
brw_glsl_base_type_for_nir_type(nir_alu_type type)
{
   switch (type) {
   case nir_type_float:
      return GLSL_TYPE_FLOAT;

   case nir_type_int:
      return GLSL_TYPE_INT;

   case nir_type_uint:
      return GLSL_TYPE_UINT;

   default:
      unreachable("bad type");
   }
}
