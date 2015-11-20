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
 *
 * Authors:
 *    Connor Abbott (cwabbott0@gmail.com)
 *
 */

#include "nir.h"
#include "nir_control_flow_private.h"
#include <assert.h>

nir_shader *
nir_shader_create(gl_shader_stage stage,
                  const nir_shader_compiler_options *options)
{
   nir_shader *shader = ralloc(NULL, nir_shader);

   exec_list_make_empty(&shader->uniforms);
   exec_list_make_empty(&shader->inputs);
   exec_list_make_empty(&shader->outputs);

   shader->options = options;
   memset(&shader->info, 0, sizeof(shader->info));

   exec_list_make_empty(&shader->functions);
   exec_list_make_empty(&shader->registers);
   exec_list_make_empty(&shader->globals);
   exec_list_make_empty(&shader->system_values);
   shader->reg_alloc = 0;

   shader->num_inputs = 0;
   shader->num_outputs = 0;
   shader->num_uniforms = 0;

   shader->stage = stage;

   return shader;
}

static nir_register *
reg_create(void *mem_ctx, struct exec_list *list)
{
   nir_register *reg = ralloc(mem_ctx, nir_register);

   list_inithead(&reg->uses);
   list_inithead(&reg->defs);
   list_inithead(&reg->if_uses);

   reg->num_components = 0;
   reg->num_array_elems = 0;
   reg->is_packed = false;
   reg->name = NULL;

   exec_list_push_tail(list, &reg->node);

   return reg;
}

nir_register *
nir_global_reg_create(nir_shader *shader)
{
   nir_register *reg = reg_create(shader, &shader->registers);
   reg->index = shader->reg_alloc++;
   reg->is_global = true;

   return reg;
}

nir_register *
nir_local_reg_create(nir_function_impl *impl)
{
   nir_register *reg = reg_create(ralloc_parent(impl), &impl->registers);
   reg->index = impl->reg_alloc++;
   reg->is_global = false;

   return reg;
}

void
nir_reg_remove(nir_register *reg)
{
   exec_node_remove(&reg->node);
}

void
nir_shader_add_variable(nir_shader *shader, nir_variable *var)
{
   switch (var->data.mode) {
   case nir_var_all:
      assert(!"invalid mode");
      break;

   case nir_var_local:
      assert(!"nir_shader_add_variable cannot be used for local variables");
      break;

   case nir_var_global:
      exec_list_push_tail(&shader->globals, &var->node);
      break;

   case nir_var_shader_in:
      exec_list_push_tail(&shader->inputs, &var->node);
      break;

   case nir_var_shader_out:
      exec_list_push_tail(&shader->outputs, &var->node);
      break;

   case nir_var_uniform:
   case nir_var_shader_storage:
      exec_list_push_tail(&shader->uniforms, &var->node);
      break;

   case nir_var_system_value:
      exec_list_push_tail(&shader->system_values, &var->node);
      break;
   }
}

nir_variable *
nir_variable_create(nir_shader *shader, nir_variable_mode mode,
                    const struct glsl_type *type, const char *name)
{
   nir_variable *var = rzalloc(shader, nir_variable);
   var->name = ralloc_strdup(var, name);
   var->type = type;
   var->data.mode = mode;

   if ((mode == nir_var_shader_in && shader->stage != MESA_SHADER_VERTEX) ||
       (mode == nir_var_shader_out && shader->stage != MESA_SHADER_FRAGMENT))
      var->data.interpolation = INTERP_QUALIFIER_SMOOTH;

   if (mode == nir_var_shader_in || mode == nir_var_uniform)
      var->data.read_only = true;

   nir_shader_add_variable(shader, var);

   return var;
}

nir_variable *
nir_local_variable_create(nir_function_impl *impl,
                          const struct glsl_type *type, const char *name)
{
   nir_variable *var = rzalloc(impl->overload->function->shader, nir_variable);
   var->name = ralloc_strdup(var, name);
   var->type = type;
   var->data.mode = nir_var_local;

   nir_function_impl_add_variable(impl, var);

   return var;
}

nir_function *
nir_function_create(nir_shader *shader, const char *name)
{
   nir_function *func = ralloc(shader, nir_function);

   exec_list_push_tail(&shader->functions, &func->node);
   exec_list_make_empty(&func->overload_list);
   func->name = ralloc_strdup(func, name);
   func->shader = shader;

   return func;
}

nir_function_overload *
nir_function_overload_create(nir_function *func)
{
   void *mem_ctx = ralloc_parent(func);

   nir_function_overload *overload = ralloc(mem_ctx, nir_function_overload);

   overload->num_params = 0;
   overload->params = NULL;
   overload->return_type = glsl_void_type();
   overload->impl = NULL;

   exec_list_push_tail(&func->overload_list, &overload->node);
   overload->function = func;

   return overload;
}

void nir_src_copy(nir_src *dest, const nir_src *src, void *mem_ctx)
{
   dest->is_ssa = src->is_ssa;
   if (src->is_ssa) {
      dest->ssa = src->ssa;
   } else {
      dest->reg.base_offset = src->reg.base_offset;
      dest->reg.reg = src->reg.reg;
      if (src->reg.indirect) {
         dest->reg.indirect = ralloc(mem_ctx, nir_src);
         nir_src_copy(dest->reg.indirect, src->reg.indirect, mem_ctx);
      } else {
         dest->reg.indirect = NULL;
      }
   }
}

void nir_dest_copy(nir_dest *dest, const nir_dest *src, nir_instr *instr)
{
   /* Copying an SSA definition makes no sense whatsoever. */
   assert(!src->is_ssa);

   dest->is_ssa = false;

   dest->reg.base_offset = src->reg.base_offset;
   dest->reg.reg = src->reg.reg;
   if (src->reg.indirect) {
      dest->reg.indirect = ralloc(instr, nir_src);
      nir_src_copy(dest->reg.indirect, src->reg.indirect, instr);
   } else {
      dest->reg.indirect = NULL;
   }
}

void
nir_alu_src_copy(nir_alu_src *dest, const nir_alu_src *src,
                 nir_alu_instr *instr)
{
   nir_src_copy(&dest->src, &src->src, &instr->instr);
   dest->abs = src->abs;
   dest->negate = src->negate;
   for (unsigned i = 0; i < 4; i++)
      dest->swizzle[i] = src->swizzle[i];
}

void
nir_alu_dest_copy(nir_alu_dest *dest, const nir_alu_dest *src,
                  nir_alu_instr *instr)
{
   nir_dest_copy(&dest->dest, &src->dest, &instr->instr);
   dest->write_mask = src->write_mask;
   dest->saturate = src->saturate;
}


static void
cf_init(nir_cf_node *node, nir_cf_node_type type)
{
   exec_node_init(&node->node);
   node->parent = NULL;
   node->type = type;
}

nir_function_impl *
nir_function_impl_create(nir_function_overload *overload)
{
   assert(overload->impl == NULL);

   void *mem_ctx = ralloc_parent(overload);

   nir_function_impl *impl = ralloc(mem_ctx, nir_function_impl);

   overload->impl = impl;
   impl->overload = overload;

   cf_init(&impl->cf_node, nir_cf_node_function);

   exec_list_make_empty(&impl->body);
   exec_list_make_empty(&impl->registers);
   exec_list_make_empty(&impl->locals);
   impl->num_params = 0;
   impl->params = NULL;
   impl->return_var = NULL;
   impl->reg_alloc = 0;
   impl->ssa_alloc = 0;
   impl->valid_metadata = nir_metadata_none;

   /* create start & end blocks */
   nir_block *start_block = nir_block_create(mem_ctx);
   nir_block *end_block = nir_block_create(mem_ctx);
   start_block->cf_node.parent = &impl->cf_node;
   end_block->cf_node.parent = &impl->cf_node;
   impl->end_block = end_block;

   exec_list_push_tail(&impl->body, &start_block->cf_node.node);

   start_block->successors[0] = end_block;
   _mesa_set_add(end_block->predecessors, start_block);
   return impl;
}

nir_block *
nir_block_create(nir_shader *shader)
{
   nir_block *block = ralloc(shader, nir_block);

   cf_init(&block->cf_node, nir_cf_node_block);

   block->successors[0] = block->successors[1] = NULL;
   block->predecessors = _mesa_set_create(block, _mesa_hash_pointer,
                                          _mesa_key_pointer_equal);
   block->imm_dom = NULL;
   /* XXX maybe it would be worth it to defer allocation?  This
    * way it doesn't get allocated for shader ref's that never run
    * nir_calc_dominance?  For example, state-tracker creates an
    * initial IR, clones that, runs appropriate lowering pass, passes
    * to driver which does common lowering/opt, and then stores ref
    * which is later used to do state specific lowering and futher
    * opt.  Do any of the references not need dominance metadata?
    */
   block->dom_frontier = _mesa_set_create(block, _mesa_hash_pointer,
                                          _mesa_key_pointer_equal);

   exec_list_make_empty(&block->instr_list);

   return block;
}

static inline void
src_init(nir_src *src)
{
   src->is_ssa = false;
   src->reg.reg = NULL;
   src->reg.indirect = NULL;
   src->reg.base_offset = 0;
}

nir_if *
nir_if_create(nir_shader *shader)
{
   nir_if *if_stmt = ralloc(shader, nir_if);

   cf_init(&if_stmt->cf_node, nir_cf_node_if);
   src_init(&if_stmt->condition);

   nir_block *then = nir_block_create(shader);
   exec_list_make_empty(&if_stmt->then_list);
   exec_list_push_tail(&if_stmt->then_list, &then->cf_node.node);
   then->cf_node.parent = &if_stmt->cf_node;

   nir_block *else_stmt = nir_block_create(shader);
   exec_list_make_empty(&if_stmt->else_list);
   exec_list_push_tail(&if_stmt->else_list, &else_stmt->cf_node.node);
   else_stmt->cf_node.parent = &if_stmt->cf_node;

   return if_stmt;
}

nir_loop *
nir_loop_create(nir_shader *shader)
{
   nir_loop *loop = ralloc(shader, nir_loop);

   cf_init(&loop->cf_node, nir_cf_node_loop);

   nir_block *body = nir_block_create(shader);
   exec_list_make_empty(&loop->body);
   exec_list_push_tail(&loop->body, &body->cf_node.node);
   body->cf_node.parent = &loop->cf_node;

   body->successors[0] = body;
   _mesa_set_add(body->predecessors, body);

   return loop;
}

static void
instr_init(nir_instr *instr, nir_instr_type type)
{
   instr->type = type;
   instr->block = NULL;
   exec_node_init(&instr->node);
}

static void
dest_init(nir_dest *dest)
{
   dest->is_ssa = false;
   dest->reg.reg = NULL;
   dest->reg.indirect = NULL;
   dest->reg.base_offset = 0;
}

static void
alu_dest_init(nir_alu_dest *dest)
{
   dest_init(&dest->dest);
   dest->saturate = false;
   dest->write_mask = 0xf;
}

static void
alu_src_init(nir_alu_src *src)
{
   src_init(&src->src);
   src->abs = src->negate = false;
   src->swizzle[0] = 0;
   src->swizzle[1] = 1;
   src->swizzle[2] = 2;
   src->swizzle[3] = 3;
}

nir_alu_instr *
nir_alu_instr_create(nir_shader *shader, nir_op op)
{
   unsigned num_srcs = nir_op_infos[op].num_inputs;
   nir_alu_instr *instr =
      ralloc_size(shader,
                  sizeof(nir_alu_instr) + num_srcs * sizeof(nir_alu_src));

   instr_init(&instr->instr, nir_instr_type_alu);
   instr->op = op;
   alu_dest_init(&instr->dest);
   for (unsigned i = 0; i < num_srcs; i++)
      alu_src_init(&instr->src[i]);

   return instr;
}

nir_jump_instr *
nir_jump_instr_create(nir_shader *shader, nir_jump_type type)
{
   nir_jump_instr *instr = ralloc(shader, nir_jump_instr);
   instr_init(&instr->instr, nir_instr_type_jump);
   instr->type = type;
   return instr;
}

nir_load_const_instr *
nir_load_const_instr_create(nir_shader *shader, unsigned num_components)
{
   nir_load_const_instr *instr = ralloc(shader, nir_load_const_instr);
   instr_init(&instr->instr, nir_instr_type_load_const);

   nir_ssa_def_init(&instr->instr, &instr->def, num_components, NULL);

   return instr;
}

nir_intrinsic_instr *
nir_intrinsic_instr_create(nir_shader *shader, nir_intrinsic_op op)
{
   unsigned num_srcs = nir_intrinsic_infos[op].num_srcs;
   nir_intrinsic_instr *instr =
      ralloc_size(shader,
                  sizeof(nir_intrinsic_instr) + num_srcs * sizeof(nir_src));

   instr_init(&instr->instr, nir_instr_type_intrinsic);
   instr->intrinsic = op;

   if (nir_intrinsic_infos[op].has_dest)
      dest_init(&instr->dest);

   for (unsigned i = 0; i < num_srcs; i++)
      src_init(&instr->src[i]);

   return instr;
}

nir_call_instr *
nir_call_instr_create(nir_shader *shader, nir_function_overload *callee)
{
   nir_call_instr *instr = ralloc(shader, nir_call_instr);
   instr_init(&instr->instr, nir_instr_type_call);

   instr->callee = callee;
   instr->num_params = callee->num_params;
   instr->params = ralloc_array(instr, nir_deref_var *, instr->num_params);
   instr->return_deref = NULL;

   return instr;
}

nir_tex_instr *
nir_tex_instr_create(nir_shader *shader, unsigned num_srcs)
{
   nir_tex_instr *instr = rzalloc(shader, nir_tex_instr);
   instr_init(&instr->instr, nir_instr_type_tex);

   dest_init(&instr->dest);

   instr->num_srcs = num_srcs;
   instr->src = ralloc_array(instr, nir_tex_src, num_srcs);
   for (unsigned i = 0; i < num_srcs; i++)
      src_init(&instr->src[i].src);

   instr->sampler_index = 0;
   instr->sampler_array_size = 0;
   instr->sampler = NULL;

   return instr;
}

nir_phi_instr *
nir_phi_instr_create(nir_shader *shader)
{
   nir_phi_instr *instr = ralloc(shader, nir_phi_instr);
   instr_init(&instr->instr, nir_instr_type_phi);

   dest_init(&instr->dest);
   exec_list_make_empty(&instr->srcs);
   return instr;
}

nir_parallel_copy_instr *
nir_parallel_copy_instr_create(nir_shader *shader)
{
   nir_parallel_copy_instr *instr = ralloc(shader, nir_parallel_copy_instr);
   instr_init(&instr->instr, nir_instr_type_parallel_copy);

   exec_list_make_empty(&instr->entries);

   return instr;
}

nir_ssa_undef_instr *
nir_ssa_undef_instr_create(nir_shader *shader, unsigned num_components)
{
   nir_ssa_undef_instr *instr = ralloc(shader, nir_ssa_undef_instr);
   instr_init(&instr->instr, nir_instr_type_ssa_undef);

   nir_ssa_def_init(&instr->instr, &instr->def, num_components, NULL);

   return instr;
}

nir_deref_var *
nir_deref_var_create(void *mem_ctx, nir_variable *var)
{
   nir_deref_var *deref = ralloc(mem_ctx, nir_deref_var);
   deref->deref.deref_type = nir_deref_type_var;
   deref->deref.child = NULL;
   deref->deref.type = var->type;
   deref->var = var;
   return deref;
}

nir_deref_array *
nir_deref_array_create(void *mem_ctx)
{
   nir_deref_array *deref = ralloc(mem_ctx, nir_deref_array);
   deref->deref.deref_type = nir_deref_type_array;
   deref->deref.child = NULL;
   deref->deref_array_type = nir_deref_array_type_direct;
   src_init(&deref->indirect);
   deref->base_offset = 0;
   return deref;
}

nir_deref_struct *
nir_deref_struct_create(void *mem_ctx, unsigned field_index)
{
   nir_deref_struct *deref = ralloc(mem_ctx, nir_deref_struct);
   deref->deref.deref_type = nir_deref_type_struct;
   deref->deref.child = NULL;
   deref->index = field_index;
   return deref;
}

static nir_deref_var *
copy_deref_var(void *mem_ctx, nir_deref_var *deref)
{
   nir_deref_var *ret = nir_deref_var_create(mem_ctx, deref->var);
   ret->deref.type = deref->deref.type;
   if (deref->deref.child)
      ret->deref.child = nir_copy_deref(ret, deref->deref.child);
   return ret;
}

static nir_deref_array *
copy_deref_array(void *mem_ctx, nir_deref_array *deref)
{
   nir_deref_array *ret = nir_deref_array_create(mem_ctx);
   ret->base_offset = deref->base_offset;
   ret->deref_array_type = deref->deref_array_type;
   if (deref->deref_array_type == nir_deref_array_type_indirect) {
      nir_src_copy(&ret->indirect, &deref->indirect, mem_ctx);
   }
   ret->deref.type = deref->deref.type;
   if (deref->deref.child)
      ret->deref.child = nir_copy_deref(ret, deref->deref.child);
   return ret;
}

static nir_deref_struct *
copy_deref_struct(void *mem_ctx, nir_deref_struct *deref)
{
   nir_deref_struct *ret = nir_deref_struct_create(mem_ctx, deref->index);
   ret->deref.type = deref->deref.type;
   if (deref->deref.child)
      ret->deref.child = nir_copy_deref(ret, deref->deref.child);
   return ret;
}

nir_deref *
nir_copy_deref(void *mem_ctx, nir_deref *deref)
{
   switch (deref->deref_type) {
   case nir_deref_type_var:
      return &copy_deref_var(mem_ctx, nir_deref_as_var(deref))->deref;
   case nir_deref_type_array:
      return &copy_deref_array(mem_ctx, nir_deref_as_array(deref))->deref;
   case nir_deref_type_struct:
      return &copy_deref_struct(mem_ctx, nir_deref_as_struct(deref))->deref;
   default:
      unreachable("Invalid dereference type");
   }

   return NULL;
}

/* Returns a load_const instruction that represents the constant
 * initializer for the given deref chain.  The caller is responsible for
 * ensuring that there actually is a constant initializer.
 */
nir_load_const_instr *
nir_deref_get_const_initializer_load(nir_shader *shader, nir_deref_var *deref)
{
   nir_constant *constant = deref->var->constant_initializer;
   assert(constant);

   const nir_deref *tail = &deref->deref;
   unsigned matrix_offset = 0;
   while (tail->child) {
      switch (tail->child->deref_type) {
      case nir_deref_type_array: {
         nir_deref_array *arr = nir_deref_as_array(tail->child);
         assert(arr->deref_array_type == nir_deref_array_type_direct);
         if (glsl_type_is_matrix(tail->type)) {
            assert(arr->deref.child == NULL);
            matrix_offset = arr->base_offset;
         } else {
            constant = constant->elements[arr->base_offset];
         }
         break;
      }

      case nir_deref_type_struct: {
         constant = constant->elements[nir_deref_as_struct(tail->child)->index];
         break;
      }

      default:
         unreachable("Invalid deref child type");
      }

      tail = tail->child;
   }

   nir_load_const_instr *load =
      nir_load_const_instr_create(shader, glsl_get_vector_elements(tail->type));

   matrix_offset *= load->def.num_components;
   for (unsigned i = 0; i < load->def.num_components; i++) {
      switch (glsl_get_base_type(tail->type)) {
      case GLSL_TYPE_FLOAT:
      case GLSL_TYPE_INT:
      case GLSL_TYPE_UINT:
         load->value.u[i] = constant->value.u[matrix_offset + i];
         break;
      case GLSL_TYPE_BOOL:
         load->value.u[i] = constant->value.b[matrix_offset + i] ?
                             NIR_TRUE : NIR_FALSE;
         break;
      default:
         unreachable("Invalid immediate type");
      }
   }

   return load;
}

nir_function_impl *
nir_cf_node_get_function(nir_cf_node *node)
{
   while (node->type != nir_cf_node_function) {
      node = node->parent;
   }

   return nir_cf_node_as_function(node);
}

static bool
add_use_cb(nir_src *src, void *state)
{
   nir_instr *instr = state;

   src->parent_instr = instr;
   list_addtail(&src->use_link,
                src->is_ssa ? &src->ssa->uses : &src->reg.reg->uses);

   return true;
}

static bool
add_ssa_def_cb(nir_ssa_def *def, void *state)
{
   nir_instr *instr = state;

   if (instr->block && def->index == UINT_MAX) {
      nir_function_impl *impl =
         nir_cf_node_get_function(&instr->block->cf_node);

      def->index = impl->ssa_alloc++;
   }

   return true;
}

static bool
add_reg_def_cb(nir_dest *dest, void *state)
{
   nir_instr *instr = state;

   if (!dest->is_ssa) {
      dest->reg.parent_instr = instr;
      list_addtail(&dest->reg.def_link, &dest->reg.reg->defs);
   }

   return true;
}

static void
add_defs_uses(nir_instr *instr)
{
   nir_foreach_src(instr, add_use_cb, instr);
   nir_foreach_dest(instr, add_reg_def_cb, instr);
   nir_foreach_ssa_def(instr, add_ssa_def_cb, instr);
}

void
nir_instr_insert(nir_cursor cursor, nir_instr *instr)
{
   switch (cursor.option) {
   case nir_cursor_before_block:
      /* Only allow inserting jumps into empty blocks. */
      if (instr->type == nir_instr_type_jump)
         assert(exec_list_is_empty(&cursor.block->instr_list));

      instr->block = cursor.block;
      add_defs_uses(instr);
      exec_list_push_head(&cursor.block->instr_list, &instr->node);
      break;
   case nir_cursor_after_block: {
      /* Inserting instructions after a jump is illegal. */
      nir_instr *last = nir_block_last_instr(cursor.block);
      assert(last == NULL || last->type != nir_instr_type_jump);
      (void) last;

      instr->block = cursor.block;
      add_defs_uses(instr);
      exec_list_push_tail(&cursor.block->instr_list, &instr->node);
      break;
   }
   case nir_cursor_before_instr:
      assert(instr->type != nir_instr_type_jump);
      instr->block = cursor.instr->block;
      add_defs_uses(instr);
      exec_node_insert_node_before(&cursor.instr->node, &instr->node);
      break;
   case nir_cursor_after_instr:
      /* Inserting instructions after a jump is illegal. */
      assert(cursor.instr->type != nir_instr_type_jump);

      /* Only allow inserting jumps at the end of the block. */
      if (instr->type == nir_instr_type_jump)
         assert(cursor.instr == nir_block_last_instr(cursor.instr->block));

      instr->block = cursor.instr->block;
      add_defs_uses(instr);
      exec_node_insert_after(&cursor.instr->node, &instr->node);
      break;
   }

   if (instr->type == nir_instr_type_jump)
      nir_handle_add_jump(instr->block);
}

static bool
src_is_valid(const nir_src *src)
{
   return src->is_ssa ? (src->ssa != NULL) : (src->reg.reg != NULL);
}

static bool
remove_use_cb(nir_src *src, void *state)
{
   if (src_is_valid(src))
      list_del(&src->use_link);

   return true;
}

static bool
remove_def_cb(nir_dest *dest, void *state)
{
   if (!dest->is_ssa)
      list_del(&dest->reg.def_link);

   return true;
}

static void
remove_defs_uses(nir_instr *instr)
{
   nir_foreach_dest(instr, remove_def_cb, instr);
   nir_foreach_src(instr, remove_use_cb, instr);
}

void nir_instr_remove(nir_instr *instr)
{
   remove_defs_uses(instr);
   exec_node_remove(&instr->node);

   if (instr->type == nir_instr_type_jump) {
      nir_jump_instr *jump_instr = nir_instr_as_jump(instr);
      nir_handle_remove_jump(instr->block, jump_instr->type);
   }
}

/*@}*/

void
nir_index_local_regs(nir_function_impl *impl)
{
   unsigned index = 0;
   foreach_list_typed(nir_register, reg, node, &impl->registers) {
      reg->index = index++;
   }
   impl->reg_alloc = index;
}

void
nir_index_global_regs(nir_shader *shader)
{
   unsigned index = 0;
   foreach_list_typed(nir_register, reg, node, &shader->registers) {
      reg->index = index++;
   }
   shader->reg_alloc = index;
}

static bool
visit_alu_dest(nir_alu_instr *instr, nir_foreach_dest_cb cb, void *state)
{
   return cb(&instr->dest.dest, state);
}

static bool
visit_intrinsic_dest(nir_intrinsic_instr *instr, nir_foreach_dest_cb cb,
                     void *state)
{
   if (nir_intrinsic_infos[instr->intrinsic].has_dest)
      return cb(&instr->dest, state);

   return true;
}

static bool
visit_texture_dest(nir_tex_instr *instr, nir_foreach_dest_cb cb,
                   void *state)
{
   return cb(&instr->dest, state);
}

static bool
visit_phi_dest(nir_phi_instr *instr, nir_foreach_dest_cb cb, void *state)
{
   return cb(&instr->dest, state);
}

static bool
visit_parallel_copy_dest(nir_parallel_copy_instr *instr,
                         nir_foreach_dest_cb cb, void *state)
{
   nir_foreach_parallel_copy_entry(instr, entry) {
      if (!cb(&entry->dest, state))
         return false;
   }

   return true;
}

bool
nir_foreach_dest(nir_instr *instr, nir_foreach_dest_cb cb, void *state)
{
   switch (instr->type) {
   case nir_instr_type_alu:
      return visit_alu_dest(nir_instr_as_alu(instr), cb, state);
   case nir_instr_type_intrinsic:
      return visit_intrinsic_dest(nir_instr_as_intrinsic(instr), cb, state);
   case nir_instr_type_tex:
      return visit_texture_dest(nir_instr_as_tex(instr), cb, state);
   case nir_instr_type_phi:
      return visit_phi_dest(nir_instr_as_phi(instr), cb, state);
   case nir_instr_type_parallel_copy:
      return visit_parallel_copy_dest(nir_instr_as_parallel_copy(instr),
                                      cb, state);

   case nir_instr_type_load_const:
   case nir_instr_type_ssa_undef:
   case nir_instr_type_call:
   case nir_instr_type_jump:
      break;

   default:
      unreachable("Invalid instruction type");
      break;
   }

   return true;
}

struct foreach_ssa_def_state {
   nir_foreach_ssa_def_cb cb;
   void *client_state;
};

static inline bool
nir_ssa_def_visitor(nir_dest *dest, void *void_state)
{
   struct foreach_ssa_def_state *state = void_state;

   if (dest->is_ssa)
      return state->cb(&dest->ssa, state->client_state);
   else
      return true;
}

bool
nir_foreach_ssa_def(nir_instr *instr, nir_foreach_ssa_def_cb cb, void *state)
{
   switch (instr->type) {
   case nir_instr_type_alu:
   case nir_instr_type_tex:
   case nir_instr_type_intrinsic:
   case nir_instr_type_phi:
   case nir_instr_type_parallel_copy: {
      struct foreach_ssa_def_state foreach_state = {cb, state};
      return nir_foreach_dest(instr, nir_ssa_def_visitor, &foreach_state);
   }

   case nir_instr_type_load_const:
      return cb(&nir_instr_as_load_const(instr)->def, state);
   case nir_instr_type_ssa_undef:
      return cb(&nir_instr_as_ssa_undef(instr)->def, state);
   case nir_instr_type_call:
   case nir_instr_type_jump:
      return true;
   default:
      unreachable("Invalid instruction type");
   }
}

static bool
visit_src(nir_src *src, nir_foreach_src_cb cb, void *state)
{
   if (!cb(src, state))
      return false;
   if (!src->is_ssa && src->reg.indirect)
      return cb(src->reg.indirect, state);
   return true;
}

static bool
visit_deref_array_src(nir_deref_array *deref, nir_foreach_src_cb cb,
                      void *state)
{
   if (deref->deref_array_type == nir_deref_array_type_indirect)
      return visit_src(&deref->indirect, cb, state);
   return true;
}

static bool
visit_deref_src(nir_deref_var *deref, nir_foreach_src_cb cb, void *state)
{
   nir_deref *cur = &deref->deref;
   while (cur != NULL) {
      if (cur->deref_type == nir_deref_type_array)
         if (!visit_deref_array_src(nir_deref_as_array(cur), cb, state))
            return false;

      cur = cur->child;
   }

   return true;
}

static bool
visit_alu_src(nir_alu_instr *instr, nir_foreach_src_cb cb, void *state)
{
   for (unsigned i = 0; i < nir_op_infos[instr->op].num_inputs; i++)
      if (!visit_src(&instr->src[i].src, cb, state))
         return false;

   return true;
}

static bool
visit_tex_src(nir_tex_instr *instr, nir_foreach_src_cb cb, void *state)
{
   for (unsigned i = 0; i < instr->num_srcs; i++)
      if (!visit_src(&instr->src[i].src, cb, state))
         return false;

   if (instr->sampler != NULL)
      if (!visit_deref_src(instr->sampler, cb, state))
         return false;

   return true;
}

static bool
visit_intrinsic_src(nir_intrinsic_instr *instr, nir_foreach_src_cb cb,
                    void *state)
{
   unsigned num_srcs = nir_intrinsic_infos[instr->intrinsic].num_srcs;
   for (unsigned i = 0; i < num_srcs; i++)
      if (!visit_src(&instr->src[i], cb, state))
         return false;

   unsigned num_vars =
      nir_intrinsic_infos[instr->intrinsic].num_variables;
   for (unsigned i = 0; i < num_vars; i++)
      if (!visit_deref_src(instr->variables[i], cb, state))
         return false;

   return true;
}

static bool
visit_call_src(nir_call_instr *instr, nir_foreach_src_cb cb, void *state)
{
   return true;
}

static bool
visit_load_const_src(nir_load_const_instr *instr, nir_foreach_src_cb cb,
                     void *state)
{
   return true;
}

static bool
visit_phi_src(nir_phi_instr *instr, nir_foreach_src_cb cb, void *state)
{
   nir_foreach_phi_src(instr, src) {
      if (!visit_src(&src->src, cb, state))
         return false;
   }

   return true;
}

static bool
visit_parallel_copy_src(nir_parallel_copy_instr *instr,
                        nir_foreach_src_cb cb, void *state)
{
   nir_foreach_parallel_copy_entry(instr, entry) {
      if (!visit_src(&entry->src, cb, state))
         return false;
   }

   return true;
}

typedef struct {
   void *state;
   nir_foreach_src_cb cb;
} visit_dest_indirect_state;

static bool
visit_dest_indirect(nir_dest *dest, void *_state)
{
   visit_dest_indirect_state *state = (visit_dest_indirect_state *) _state;

   if (!dest->is_ssa && dest->reg.indirect)
      return state->cb(dest->reg.indirect, state->state);

   return true;
}

bool
nir_foreach_src(nir_instr *instr, nir_foreach_src_cb cb, void *state)
{
   switch (instr->type) {
   case nir_instr_type_alu:
      if (!visit_alu_src(nir_instr_as_alu(instr), cb, state))
         return false;
      break;
   case nir_instr_type_intrinsic:
      if (!visit_intrinsic_src(nir_instr_as_intrinsic(instr), cb, state))
         return false;
      break;
   case nir_instr_type_tex:
      if (!visit_tex_src(nir_instr_as_tex(instr), cb, state))
         return false;
      break;
   case nir_instr_type_call:
      if (!visit_call_src(nir_instr_as_call(instr), cb, state))
         return false;
      break;
   case nir_instr_type_load_const:
      if (!visit_load_const_src(nir_instr_as_load_const(instr), cb, state))
         return false;
      break;
   case nir_instr_type_phi:
      if (!visit_phi_src(nir_instr_as_phi(instr), cb, state))
         return false;
      break;
   case nir_instr_type_parallel_copy:
      if (!visit_parallel_copy_src(nir_instr_as_parallel_copy(instr),
                                   cb, state))
         return false;
      break;
   case nir_instr_type_jump:
   case nir_instr_type_ssa_undef:
      return true;

   default:
      unreachable("Invalid instruction type");
      break;
   }

   visit_dest_indirect_state dest_state;
   dest_state.state = state;
   dest_state.cb = cb;
   return nir_foreach_dest(instr, visit_dest_indirect, &dest_state);
}

nir_const_value *
nir_src_as_const_value(nir_src src)
{
   if (!src.is_ssa)
      return NULL;

   if (src.ssa->parent_instr->type != nir_instr_type_load_const)
      return NULL;

   nir_load_const_instr *load = nir_instr_as_load_const(src.ssa->parent_instr);

   return &load->value;
}

/**
 * Returns true if the source is known to be dynamically uniform. Otherwise it
 * returns false which means it may or may not be dynamically uniform but it
 * can't be determined.
 */
bool
nir_src_is_dynamically_uniform(nir_src src)
{
   if (!src.is_ssa)
      return false;

   /* Constants are trivially dynamically uniform */
   if (src.ssa->parent_instr->type == nir_instr_type_load_const)
      return true;

   /* As are uniform variables */
   if (src.ssa->parent_instr->type == nir_instr_type_intrinsic) {
      nir_intrinsic_instr *intr = nir_instr_as_intrinsic(src.ssa->parent_instr);

      if (intr->intrinsic == nir_intrinsic_load_uniform)
         return true;
   }

   /* XXX: this could have many more tests, such as when a sampler function is
    * called with dynamically uniform arguments.
    */
   return false;
}

static void
src_remove_all_uses(nir_src *src)
{
   for (; src; src = src->is_ssa ? NULL : src->reg.indirect) {
      if (!src_is_valid(src))
         continue;

      list_del(&src->use_link);
   }
}

static void
src_add_all_uses(nir_src *src, nir_instr *parent_instr, nir_if *parent_if)
{
   for (; src; src = src->is_ssa ? NULL : src->reg.indirect) {
      if (!src_is_valid(src))
         continue;

      if (parent_instr) {
         src->parent_instr = parent_instr;
         if (src->is_ssa)
            list_addtail(&src->use_link, &src->ssa->uses);
         else
            list_addtail(&src->use_link, &src->reg.reg->uses);
      } else {
         assert(parent_if);
         src->parent_if = parent_if;
         if (src->is_ssa)
            list_addtail(&src->use_link, &src->ssa->if_uses);
         else
            list_addtail(&src->use_link, &src->reg.reg->if_uses);
      }
   }
}

void
nir_instr_rewrite_src(nir_instr *instr, nir_src *src, nir_src new_src)
{
   assert(!src_is_valid(src) || src->parent_instr == instr);

   src_remove_all_uses(src);
   *src = new_src;
   src_add_all_uses(src, instr, NULL);
}

void
nir_instr_move_src(nir_instr *dest_instr, nir_src *dest, nir_src *src)
{
   assert(!src_is_valid(dest) || dest->parent_instr == dest_instr);

   src_remove_all_uses(dest);
   src_remove_all_uses(src);
   *dest = *src;
   *src = NIR_SRC_INIT;
   src_add_all_uses(dest, dest_instr, NULL);
}

void
nir_if_rewrite_condition(nir_if *if_stmt, nir_src new_src)
{
   nir_src *src = &if_stmt->condition;
   assert(!src_is_valid(src) || src->parent_if == if_stmt);

   src_remove_all_uses(src);
   *src = new_src;
   src_add_all_uses(src, NULL, if_stmt);
}

void
nir_instr_rewrite_dest(nir_instr *instr, nir_dest *dest, nir_dest new_dest)
{
   if (dest->is_ssa) {
      /* We can only overwrite an SSA destination if it has no uses. */
      assert(list_empty(&dest->ssa.uses) && list_empty(&dest->ssa.if_uses));
   } else {
      list_del(&dest->reg.def_link);
      if (dest->reg.indirect)
         src_remove_all_uses(dest->reg.indirect);
   }

   /* We can't re-write with an SSA def */
   assert(!new_dest.is_ssa);

   nir_dest_copy(dest, &new_dest, instr);

   dest->reg.parent_instr = instr;
   list_addtail(&dest->reg.def_link, &new_dest.reg.reg->defs);

   if (dest->reg.indirect)
      src_add_all_uses(dest->reg.indirect, instr, NULL);
}

void
nir_ssa_def_init(nir_instr *instr, nir_ssa_def *def,
                 unsigned num_components, const char *name)
{
   def->name = name;
   def->parent_instr = instr;
   list_inithead(&def->uses);
   list_inithead(&def->if_uses);
   def->num_components = num_components;

   if (instr->block) {
      nir_function_impl *impl =
         nir_cf_node_get_function(&instr->block->cf_node);

      def->index = impl->ssa_alloc++;
   } else {
      def->index = UINT_MAX;
   }
}

void
nir_ssa_dest_init(nir_instr *instr, nir_dest *dest,
                 unsigned num_components, const char *name)
{
   dest->is_ssa = true;
   nir_ssa_def_init(instr, &dest->ssa, num_components, name);
}

void
nir_ssa_def_rewrite_uses(nir_ssa_def *def, nir_src new_src)
{
   assert(!new_src.is_ssa || def != new_src.ssa);

   nir_foreach_use_safe(def, use_src) {
      nir_instr *src_parent_instr = use_src->parent_instr;
      list_del(&use_src->use_link);
      nir_src_copy(use_src, &new_src, src_parent_instr);
      src_add_all_uses(use_src, src_parent_instr, NULL);
   }

   nir_foreach_if_use_safe(def, use_src) {
      nir_if *src_parent_if = use_src->parent_if;
      list_del(&use_src->use_link);
      nir_src_copy(use_src, &new_src, src_parent_if);
      src_add_all_uses(use_src, NULL, src_parent_if);
   }
}


static bool foreach_cf_node(nir_cf_node *node, nir_foreach_block_cb cb,
                            bool reverse, void *state);

static inline bool
foreach_if(nir_if *if_stmt, nir_foreach_block_cb cb, bool reverse, void *state)
{
   if (reverse) {
      foreach_list_typed_safe_reverse(nir_cf_node, node, node,
                                      &if_stmt->else_list) {
         if (!foreach_cf_node(node, cb, reverse, state))
            return false;
      }

      foreach_list_typed_safe_reverse(nir_cf_node, node, node,
                                      &if_stmt->then_list) {
         if (!foreach_cf_node(node, cb, reverse, state))
            return false;
      }
   } else {
      foreach_list_typed_safe(nir_cf_node, node, node, &if_stmt->then_list) {
         if (!foreach_cf_node(node, cb, reverse, state))
            return false;
      }

      foreach_list_typed_safe(nir_cf_node, node, node, &if_stmt->else_list) {
         if (!foreach_cf_node(node, cb, reverse, state))
            return false;
      }
   }

   return true;
}

static inline bool
foreach_loop(nir_loop *loop, nir_foreach_block_cb cb, bool reverse, void *state)
{
   if (reverse) {
      foreach_list_typed_safe_reverse(nir_cf_node, node, node, &loop->body) {
         if (!foreach_cf_node(node, cb, reverse, state))
            return false;
      }
   } else {
      foreach_list_typed_safe(nir_cf_node, node, node, &loop->body) {
         if (!foreach_cf_node(node, cb, reverse, state))
            return false;
      }
   }

   return true;
}

static bool
foreach_cf_node(nir_cf_node *node, nir_foreach_block_cb cb,
                bool reverse, void *state)
{
   switch (node->type) {
   case nir_cf_node_block:
      return cb(nir_cf_node_as_block(node), state);
   case nir_cf_node_if:
      return foreach_if(nir_cf_node_as_if(node), cb, reverse, state);
   case nir_cf_node_loop:
      return foreach_loop(nir_cf_node_as_loop(node), cb, reverse, state);
      break;

   default:
      unreachable("Invalid CFG node type");
      break;
   }

   return false;
}

bool
nir_foreach_block_in_cf_node(nir_cf_node *node, nir_foreach_block_cb cb,
                             void *state)
{
   return foreach_cf_node(node, cb, false, state);
}

bool
nir_foreach_block(nir_function_impl *impl, nir_foreach_block_cb cb, void *state)
{
   foreach_list_typed_safe(nir_cf_node, node, node, &impl->body) {
      if (!foreach_cf_node(node, cb, false, state))
         return false;
   }

   return cb(impl->end_block, state);
}

bool
nir_foreach_block_reverse(nir_function_impl *impl, nir_foreach_block_cb cb,
                          void *state)
{
   if (!cb(impl->end_block, state))
      return false;

   foreach_list_typed_safe_reverse(nir_cf_node, node, node, &impl->body) {
      if (!foreach_cf_node(node, cb, true, state))
         return false;
   }

   return true;
}

nir_if *
nir_block_get_following_if(nir_block *block)
{
   if (exec_node_is_tail_sentinel(&block->cf_node.node))
      return NULL;

   if (nir_cf_node_is_last(&block->cf_node))
      return NULL;

   nir_cf_node *next_node = nir_cf_node_next(&block->cf_node);

   if (next_node->type != nir_cf_node_if)
      return NULL;

   return nir_cf_node_as_if(next_node);
}

nir_loop *
nir_block_get_following_loop(nir_block *block)
{
   if (exec_node_is_tail_sentinel(&block->cf_node.node))
      return NULL;

   if (nir_cf_node_is_last(&block->cf_node))
      return NULL;

   nir_cf_node *next_node = nir_cf_node_next(&block->cf_node);

   if (next_node->type != nir_cf_node_loop)
      return NULL;

   return nir_cf_node_as_loop(next_node);
}
static bool
index_block(nir_block *block, void *state)
{
   unsigned *index = state;
   block->index = (*index)++;
   return true;
}

void
nir_index_blocks(nir_function_impl *impl)
{
   unsigned index = 0;

   if (impl->valid_metadata & nir_metadata_block_index)
      return;

   nir_foreach_block(impl, index_block, &index);

   impl->num_blocks = index;
}

static bool
index_ssa_def_cb(nir_ssa_def *def, void *state)
{
   unsigned *index = (unsigned *) state;
   def->index = (*index)++;

   return true;
}

static bool
index_ssa_block(nir_block *block, void *state)
{
   nir_foreach_instr(block, instr)
      nir_foreach_ssa_def(instr, index_ssa_def_cb, state);

   return true;
}

/**
 * The indices are applied top-to-bottom which has the very nice property
 * that, if A dominates B, then A->index <= B->index.
 */
void
nir_index_ssa_defs(nir_function_impl *impl)
{
   unsigned index = 0;
   nir_foreach_block(impl, index_ssa_block, &index);
   impl->ssa_alloc = index;
}

static bool
index_instrs_block(nir_block *block, void *state)
{
   unsigned *index = state;
   nir_foreach_instr(block, instr)
      instr->index = (*index)++;

   return true;
}

/**
 * The indices are applied top-to-bottom which has the very nice property
 * that, if A dominates B, then A->index <= B->index.
 */
unsigned
nir_index_instrs(nir_function_impl *impl)
{
   unsigned index = 0;
   nir_foreach_block(impl, index_instrs_block, &index);
   return index;
}

nir_intrinsic_op
nir_intrinsic_from_system_value(gl_system_value val)
{
   switch (val) {
   case SYSTEM_VALUE_VERTEX_ID:
      return nir_intrinsic_load_vertex_id;
   case SYSTEM_VALUE_INSTANCE_ID:
      return nir_intrinsic_load_instance_id;
   case SYSTEM_VALUE_VERTEX_ID_ZERO_BASE:
      return nir_intrinsic_load_vertex_id_zero_base;
   case SYSTEM_VALUE_BASE_VERTEX:
      return nir_intrinsic_load_base_vertex;
   case SYSTEM_VALUE_INVOCATION_ID:
      return nir_intrinsic_load_invocation_id;
   case SYSTEM_VALUE_FRONT_FACE:
      return nir_intrinsic_load_front_face;
   case SYSTEM_VALUE_SAMPLE_ID:
      return nir_intrinsic_load_sample_id;
   case SYSTEM_VALUE_SAMPLE_POS:
      return nir_intrinsic_load_sample_pos;
   case SYSTEM_VALUE_SAMPLE_MASK_IN:
      return nir_intrinsic_load_sample_mask_in;
   case SYSTEM_VALUE_LOCAL_INVOCATION_ID:
      return nir_intrinsic_load_local_invocation_id;
   case SYSTEM_VALUE_WORK_GROUP_ID:
      return nir_intrinsic_load_work_group_id;
   case SYSTEM_VALUE_NUM_WORK_GROUPS:
      return nir_intrinsic_load_num_work_groups;
   case SYSTEM_VALUE_PRIMITIVE_ID:
      return nir_intrinsic_load_primitive_id;
   case SYSTEM_VALUE_TESS_COORD:
      return nir_intrinsic_load_tess_coord;
   case SYSTEM_VALUE_TESS_LEVEL_OUTER:
      return nir_intrinsic_load_tess_level_outer;
   case SYSTEM_VALUE_TESS_LEVEL_INNER:
      return nir_intrinsic_load_tess_level_inner;
   case SYSTEM_VALUE_VERTICES_IN:
      return nir_intrinsic_load_patch_vertices_in;
   default:
      unreachable("system value does not directly correspond to intrinsic");
   }
}

gl_system_value
nir_system_value_from_intrinsic(nir_intrinsic_op intrin)
{
   switch (intrin) {
   case nir_intrinsic_load_vertex_id:
      return SYSTEM_VALUE_VERTEX_ID;
   case nir_intrinsic_load_instance_id:
      return SYSTEM_VALUE_INSTANCE_ID;
   case nir_intrinsic_load_vertex_id_zero_base:
      return SYSTEM_VALUE_VERTEX_ID_ZERO_BASE;
   case nir_intrinsic_load_base_vertex:
      return SYSTEM_VALUE_BASE_VERTEX;
   case nir_intrinsic_load_invocation_id:
      return SYSTEM_VALUE_INVOCATION_ID;
   case nir_intrinsic_load_front_face:
      return SYSTEM_VALUE_FRONT_FACE;
   case nir_intrinsic_load_sample_id:
      return SYSTEM_VALUE_SAMPLE_ID;
   case nir_intrinsic_load_sample_pos:
      return SYSTEM_VALUE_SAMPLE_POS;
   case nir_intrinsic_load_sample_mask_in:
      return SYSTEM_VALUE_SAMPLE_MASK_IN;
   case nir_intrinsic_load_local_invocation_id:
      return SYSTEM_VALUE_LOCAL_INVOCATION_ID;
   case nir_intrinsic_load_num_work_groups:
      return SYSTEM_VALUE_NUM_WORK_GROUPS;
   case nir_intrinsic_load_work_group_id:
      return SYSTEM_VALUE_WORK_GROUP_ID;
   case nir_intrinsic_load_primitive_id:
      return SYSTEM_VALUE_PRIMITIVE_ID;
   case nir_intrinsic_load_tess_coord:
      return SYSTEM_VALUE_TESS_COORD;
   case nir_intrinsic_load_tess_level_outer:
      return SYSTEM_VALUE_TESS_LEVEL_OUTER;
   case nir_intrinsic_load_tess_level_inner:
      return SYSTEM_VALUE_TESS_LEVEL_INNER;
   case nir_intrinsic_load_patch_vertices_in:
      return SYSTEM_VALUE_VERTICES_IN;
   default:
      unreachable("intrinsic doesn't produce a system value");
   }
}
