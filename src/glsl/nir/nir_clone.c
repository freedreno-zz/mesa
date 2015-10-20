/*
 * Copyright © 2015 Red Hat
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

#include "nir.h"
#include "nir_control_flow_private.h"

// TODO move these:
#define exec_list_head(type, list, node) \
   exec_node_data(type, exec_list_get_head(list), node)
#define exec_list_next(type, nodeptr, node) \
   exec_node_data(type, exec_node_get_next(nodeptr), node)

/* Secret Decoder Ring:
 *   clone_foo():
 *        Allocate and clone a foo.
 *   __clone_foo():
 *        Clone body of foo (ie. parent class, embedded struct,
 *        etc)
 *   __clone_foo_p2():
 *        clone body of foo, pass 2.. since in first pass we
 *        can have fwd references to embedded structs, some
 *        ptrs (and things that depend on them) must be
 *        resolved in 2nd pass
 */

typedef struct {
   /* maps orig ptr -> cloned ptr: */
   struct hash_table *ptr_table;
   /* list of unresolved ssa src's: */
   struct list_head ssa_src_list;

   /* memctx for new toplevel shader object: */
   void *mem_ctx;
   /* new shader object, used as memctx for just about everything else: */
   nir_shader *ns;
} clone_state;

typedef void *(*clone_fxn)(clone_state *state, const void *ptr);

static void
init_clone_state(clone_state *state, void *mem_ctx)
{
   state->ptr_table = _mesa_hash_table_create(NULL, _mesa_hash_pointer,
                                              _mesa_key_pointer_equal);
   list_inithead(&state->ssa_src_list);
   state->mem_ctx = mem_ctx;
}

static void
free_clone_state(clone_state *state)
{
   _mesa_hash_table_destroy(state->ptr_table, NULL);
}

static void *
clone_ptr(clone_state *state, const void *ptr, clone_fxn clone)
{
   struct hash_entry *entry;
   void *nptr;

   if (!ptr)
      return NULL;

   entry = _mesa_hash_table_search(state->ptr_table, ptr);
   if (entry)
      return entry->data;

   nptr = clone(state, ptr);

#ifdef DEBUG
   entry = _mesa_hash_table_search(state->ptr_table, ptr);
   assert(entry->data == nptr);
#endif

   return nptr;
}

/* To avoid loops, we need to store cloned ptrs before they are fully
 * initialized, since cloning their contents could result in a path
 * back to the cloned pointer
 */
static void
store_ptr(clone_state *state, void *nptr, const void *ptr)
{
   _mesa_hash_table_insert(state->ptr_table, ptr, nptr);
}

/* There are a few cases we need to know the ralloc_parent()'s clone.
 * This only works when the original ptr's ralloc_parent() has already
 * been cloned, but for parents this should always be the case.
 */
static void *
ralloc_parent_clone(clone_state *state, const void *ptr)
{
   return clone_ptr(state, ralloc_parent(ptr), NULL);
}

static void * clone_var(clone_state *state, const void *ptr);
static void * clone_reg(clone_state *state, const void *ptr);
static void * clone_src(clone_state *state, const void *ptr);
static void * clone_deref(clone_state *state, const void *ptr);
static void * clone_instr(clone_state *state, const void *ptr);
static void * clone_block(clone_state *state, const void *ptr);
static void * clone_cf_node(clone_state *state, const void *ptr);
static void * clone_function_overload(clone_state *state, const void *ptr);
static void * clone_function(clone_state *state, const void *ptr);

static void __clone_cf_node_p2(clone_state *state, nir_cf_node *ncf, const nir_cf_node *cf);

/* clone list of nir_variable: */
static void
clone_var_list(clone_state *state, struct exec_list *dst,
               const struct exec_list *list)
{
   exec_list_make_empty(dst);
   foreach_list_typed(nir_variable, var, node, list) {
      nir_variable *nvar = clone_ptr(state, var, clone_var);
      exec_list_push_tail(dst, &nvar->node);
   }
}

/* clone list of nir_register: */
static void
clone_reg_list(clone_state *state, struct exec_list *dst,
               const struct exec_list *list)
{
   exec_list_make_empty(dst);
   foreach_list_typed(nir_register, reg, node, list) {
      nir_register *nreg = clone_ptr(state, reg, clone_reg);
      exec_list_push_tail(dst, &nreg->node);
   }
}

/* clone list of nir_cf_node: */
static void
clone_cf_list(clone_state *state, struct exec_list *dst,
              const struct exec_list *list)
{
   exec_list_make_empty(dst);
   foreach_list_typed(nir_cf_node, cf, node, list) {
      nir_cf_node *ncf = clone_ptr(state, cf, clone_cf_node);
      exec_list_push_tail(dst, &ncf->node);
   }
}

static void
__clone_cf_list_p2(clone_state *state, struct exec_list *dst,
                   const struct exec_list *list)
{
   nir_cf_node *ncf = exec_list_head(nir_cf_node, dst, node);
   foreach_list_typed(nir_cf_node, cf, node, list) {
      __clone_cf_node_p2(state, ncf, cf);
      ncf = exec_list_next(nir_cf_node, &ncf->node, node);
   }
}

static struct set *
clone_set(clone_state *state, void *mem_ctx, struct set *src, clone_fxn clone)
{
   struct set *dst = _mesa_set_create(mem_ctx, src->key_hash_function,
                                      src->key_equals_function);
   struct set_entry *entry;
   set_foreach(src, entry) {
      _mesa_set_add(dst, clone_ptr(state, entry->key, clone));
   }
   return dst;
}

static void *
clone_constant(clone_state *state, const void *ptr)
{
   const nir_constant *c = ptr;
   nir_constant *nc;

   void *mem_ctx = ralloc_parent_clone(state, c);

   nc = ralloc(mem_ctx, nir_constant);
   store_ptr(state, nc, c);

   nc->value = c->value;
   nc->num_elements = c->num_elements;
   nc->elements = ralloc_array(mem_ctx, nir_constant *, c->num_elements);
   for (unsigned i = 0; i < c->num_elements; i++) {
      nc->elements[i] = clone_ptr(state, c->elements[i], clone_constant);
   }

   return nc;
}

/* NOTE: for cloning nir_variable's, bypass nir_variable_create to avoid
 * having to deal with locals and globals separately:
 */
static void *
clone_var(clone_state *state, const void *ptr)
{
   const nir_variable *var = ptr;
   nir_variable *nvar;

   nvar = rzalloc(state->ns, nir_variable);
   store_ptr(state, nvar, var);

   nvar->type = var->type;
   nvar->name = ralloc_strdup(nvar, var->name);
   nvar->data = var->data;
   nvar->num_state_slots = var->num_state_slots;
   nvar->state_slots = ralloc_array(nvar, nir_state_slot, var->num_state_slots);
   memcpy(nvar->state_slots, var->state_slots,
          var->num_state_slots * sizeof(nir_state_slot));
   nvar->constant_initializer = clone_ptr(state, var->constant_initializer,
                                          clone_constant);
   nvar->interface_type = var->interface_type;

   return nvar;
}

/* NOTE: for cloning nir_register's, bypass nir_global/local_reg_create()
 * to avoid having to deal with locals and globals separately:
 */
static void *
clone_reg(clone_state *state, const void *ptr)
{
   const nir_register *reg = ptr;
   nir_register *nreg;

   nreg = rzalloc(state->ns, nir_register);
   store_ptr(state, nreg, reg);

   nreg->num_components = reg->num_components;
   nreg->num_array_elems = reg->num_array_elems;
   nreg->index = reg->index;
   nreg->name = ralloc_strdup(nreg, reg->name);
   nreg->is_global = reg->is_global;
   nreg->is_packed = reg->is_packed;

   /* reconstructing uses/defs/if_uses handled by nir_instr_insert() */
   list_inithead(&nreg->uses);
   list_inithead(&nreg->defs);
   list_inithead(&nreg->if_uses);

   return nreg;
}

static void
__clone_src(clone_state *state, nir_src *nsrc, const nir_src *src)
{
   nsrc->is_ssa = src->is_ssa;
   if (src->is_ssa) {
      /* save for resolving later... temporarily re-purpose use_link
       * (which is safe because we are done with it before we
       * nir_add_defs_uses()..)
       */
      list_addtail(&nsrc->use_link, &state->ssa_src_list);
      /* we also need to stash the original src for use to later
       * resolve the clone'd ssa-def.  Normally it would be nice
       * to keep nsrc->ssa ptr as null to catch anyone deref'ing
       * it before it is resolved.  But there wasn't room to add
       * a ptr to nir_src without increasing it's size.  But a
       * 'bitwise not' is easily reversable and should mostly
       * have the same result as null:
       */
      nsrc->ssa = (void *)~(uintptr_t)src;
   } else {
      nsrc->reg.reg = clone_ptr(state, src->reg.reg, clone_reg);
      nsrc->reg.indirect = clone_ptr(state, src->reg.indirect, clone_src);
      nsrc->reg.base_offset = src->reg.base_offset;
   }
}

static void *
clone_src(clone_state *state, const void *ptr)
{
   const nir_src *src = ptr;
   nir_src *nsrc;

   nsrc = ralloc(ralloc_parent_clone(state, src), nir_src);
   store_ptr(state, nsrc, src);

   __clone_src(state, nsrc, src);

   return nsrc;
}

static void
__clone_ssa_def(clone_state *state, nir_ssa_def *ndef, const nir_ssa_def *def)
{
   ndef->name = ralloc_strdup(state->ns, def->name);
   ndef->index = def->index;
   ndef->live_index = def->live_index;
   ndef->parent_instr = clone_ptr(state, def->parent_instr, clone_instr);
   list_inithead(&ndef->uses);
   list_inithead(&ndef->if_uses);
   ndef->num_components = def->num_components;

   /* special case, since embedded ptr linked to elsewhere, we must store it: */
   store_ptr(state, ndef, def);
}

static void
__clone_dst(clone_state *state, nir_dest *ndst, const nir_dest *dst)
{
   ndst->is_ssa = dst->is_ssa;
   if (dst->is_ssa) {
      __clone_ssa_def(state, &ndst->ssa, &dst->ssa);
   } else {
      ndst->reg.parent_instr = clone_ptr(state, dst->reg.parent_instr,
                                         clone_instr);
      ndst->reg.reg = clone_ptr(state, dst->reg.reg, clone_reg);
      ndst->reg.indirect = clone_ptr(state, dst->reg.indirect, clone_src);
      ndst->reg.base_offset = dst->reg.base_offset;
   }
}

static void
__clone_deref(clone_state *state, nir_deref *ndref, const nir_deref *dref)
{
   ndref->deref_type = dref->deref_type;
   ndref->child = clone_ptr(state, dref->child, clone_deref);
   ndref->type = dref->type;
}

static void *
clone_deref_var(clone_state *state, const void *ptr)
{
   const nir_deref_var *dvar = ptr;
   nir_deref_var *ndvar;

   ndvar = ralloc(ralloc_parent_clone(state, dvar), nir_deref_var);
   store_ptr(state, ndvar, dvar);

   __clone_deref(state, &ndvar->deref, &dvar->deref);

   ndvar->var = clone_ptr(state, dvar->var, clone_var);

   return ndvar;
}

static void *
clone_deref_array(clone_state *state, const void *ptr)
{
   const nir_deref_array *darr = ptr;
   nir_deref_array *ndarr;

   ndarr = ralloc(ralloc_parent_clone(state, darr), nir_deref_array);
   store_ptr(state, ndarr, darr);

   __clone_deref(state, &ndarr->deref, &darr->deref);

   ndarr->deref_array_type = darr->deref_array_type;
   ndarr->base_offset = darr->base_offset;

   __clone_src(state, &ndarr->indirect, &darr->indirect);

   return ndarr;
}

static void *
clone_deref_struct(clone_state *state, const void *ptr)
{
   const nir_deref_struct *dstr = ptr;
   nir_deref_struct *ndstr;

   ndstr = ralloc(ralloc_parent_clone(state, dstr), nir_deref_struct);
   store_ptr(state, ndstr, dstr);

   __clone_deref(state, &ndstr->deref, &dstr->deref);

   ndstr->index = dstr->index;

   return ndstr;
}

static void *
clone_deref(clone_state *state, const void *ptr)
{
   const nir_deref *dref = ptr;
   switch (dref->deref_type) {
   case nir_deref_type_var:
      return clone_deref_var(state, ptr);
   case nir_deref_type_array:
      return clone_deref_array(state, ptr);
   case nir_deref_type_struct:
      return clone_deref_struct(state, ptr);
   default:
      unreachable("bad deref type");
      return NULL;
   }
}

static void
__clone_instr(clone_state *state, nir_instr *ninstr, const nir_instr *instr)
{
   ninstr->type = instr->type;
   ninstr->block = clone_ptr(state, instr->block, clone_block);
}

static void *
clone_alu(clone_state *state, const void *ptr)
{
   const nir_alu_instr *alu = ptr;
   unsigned num_srcs = nir_op_infos[alu->op].num_inputs;

   nir_alu_instr *nalu =
      ralloc_size(state->ns,
                  sizeof(nir_alu_instr) + num_srcs * sizeof(nir_alu_src));
   store_ptr(state, nalu, alu);

   __clone_instr(state, &nalu->instr, &alu->instr);

   nalu->op = alu->op;

   __clone_dst(state, &nalu->dest.dest, &alu->dest.dest);
   nalu->dest.saturate = alu->dest.saturate;
   nalu->dest.write_mask = alu->dest.write_mask;

   for (unsigned i = 0; i < num_srcs; i++) {
      __clone_src(state, &nalu->src[i].src, &alu->src[i].src);
      nalu->src[i].negate = alu->src[i].negate;
      nalu->src[i].abs = alu->src[i].abs;
      memcpy(nalu->src[i].swizzle, alu->src[i].swizzle,
             sizeof(nalu->src[i].swizzle));
   }

   return nalu;
}

static void *
clone_intrinsic(clone_state *state, const void *ptr)
{
   const nir_intrinsic_instr *itr = ptr;
   unsigned num_srcs = nir_intrinsic_infos[itr->intrinsic].num_srcs;

   nir_intrinsic_instr *nitr =
      ralloc_size(state->ns,
                  sizeof(nir_intrinsic_instr) + num_srcs * sizeof(nir_src));
   store_ptr(state, nitr, itr);

   __clone_instr(state, &nitr->instr, &itr->instr);

   nitr->intrinsic = itr->intrinsic;

   if (nir_intrinsic_infos[itr->intrinsic].has_dest)
      __clone_dst(state, &nitr->dest, &itr->dest);

   nitr->num_components = itr->num_components;
   memcpy(nitr->const_index, itr->const_index, sizeof(nitr->const_index));

   for (unsigned i = 0; i < ARRAY_SIZE(nitr->variables); i++) {
      nitr->variables[i] = clone_ptr(state, itr->variables[i], clone_deref_var);
   }

   for (unsigned i = 0; i < num_srcs; i++) {
      __clone_src(state, &nitr->src[i], &itr->src[i]);
   }

   return nitr;
}

static void *
clone_load_const(clone_state *state, const void *ptr)
{
   const nir_load_const_instr *lc = ptr;
   nir_load_const_instr *nlc;

   nlc = ralloc(state->ns, nir_load_const_instr);
   store_ptr(state, nlc, lc);

   __clone_instr(state, &nlc->instr, &lc->instr);

   memcpy(&nlc->value, &lc->value, sizeof(nlc->value));
   __clone_ssa_def(state, &nlc->def, &lc->def);

   return nlc;
}

static void *
clone_ssa_undef(clone_state *state, const void *ptr)
{
   const nir_ssa_undef_instr *sa = ptr;
   nir_ssa_undef_instr *nsa;

   nsa = ralloc(state->ns, nir_ssa_undef_instr);
   store_ptr(state, nsa, sa);

   __clone_instr(state, &nsa->instr, &sa->instr);

   __clone_ssa_def(state, &nsa->def, &sa->def);

   return nsa;
}

static void *
clone_tex(clone_state *state, const void *ptr)
{
   const nir_tex_instr *tex = ptr;
   nir_tex_instr *ntex;

   ntex= ralloc(state->ns, nir_tex_instr);
   store_ptr(state, ntex, tex);

   __clone_instr(state, &ntex->instr, &tex->instr);

   ntex->sampler_dim = tex->sampler_dim;
   ntex->dest_type = tex->dest_type;
   ntex->op = tex->op;
   __clone_dst(state, &ntex->dest, &tex->dest);
   ntex->num_srcs = tex->num_srcs;
   ntex->src = ralloc_array(ntex, nir_tex_src, tex->num_srcs);
   for (unsigned i = 0; i < ntex->num_srcs; i++) {
      ntex->src[i].src_type = tex->src[i].src_type;
      __clone_src(state, &ntex->src[i].src, &tex->src[i].src);
   }
   ntex->coord_components = tex->coord_components;
   ntex->is_array = tex->is_array;
   ntex->is_shadow = tex->is_shadow;
   ntex->is_new_style_shadow = tex->is_new_style_shadow;
   memcpy(ntex->const_offset, tex->const_offset, sizeof(ntex->const_offset));
   ntex->component = tex->component;
   ntex->sampler_index = tex->sampler_index;
   ntex->sampler_array_size = tex->sampler_array_size;
   ntex->sampler = clone_ptr(state, tex->sampler, clone_deref_var);

   return ntex;
}

static void *
clone_phi(clone_state *state, const void *ptr)
{
   const nir_phi_instr *phi = ptr;
   nir_phi_instr *nphi;

   nphi = ralloc(state->ns, nir_phi_instr);
   store_ptr(state, nphi, phi);

   __clone_instr(state, &nphi->instr, &phi->instr);

   exec_list_make_empty(&nphi->srcs);
   foreach_list_typed(nir_phi_src, src, node, &phi->srcs) {
      nir_phi_src *nsrc = ralloc(nphi, nir_phi_src);

      nsrc->pred = clone_ptr(state, src->pred, clone_block);
      __clone_src(state, &nsrc->src, &src->src);

      exec_list_push_tail(&nphi->srcs, &nsrc->node);
   }

   __clone_dst(state, &nphi->dest, &phi->dest);

   return nphi;
}

static void *
clone_jump(clone_state *state, const void *ptr)
{
   const nir_jump_instr *jmp = ptr;
   nir_jump_instr *njmp;

   njmp = ralloc(state->ns, nir_jump_instr);
   store_ptr(state, njmp, jmp);

   __clone_instr(state, &njmp->instr, &jmp->instr);

   njmp->type = jmp->type;

   return njmp;
}

static void *
clone_call(clone_state *state, const void *ptr)
{
   const nir_call_instr *call = ptr;
   nir_call_instr *ncall;

   ncall = ralloc(state->ns, nir_call_instr);
   store_ptr(state, ncall, call);

   __clone_instr(state, &ncall->instr, &call->instr);

   ncall->num_params = call->num_params;
   ncall->params = ralloc_array(ncall, nir_deref_var *, call->num_params);
   for (unsigned i = 0; i < ncall->num_params; i++) {
      ncall->params[i] = clone_ptr(state, call->params[i], clone_deref_var);
   }

   ncall->return_deref = clone_ptr(state, call->return_deref, clone_deref_var);
   ncall->callee = clone_ptr(state, call->callee, clone_function_overload);

   return ncall;
}

static void *
clone_parallel_copy(clone_state *state, const void *ptr)
{
   const nir_parallel_copy_instr *pc = ptr;
   nir_parallel_copy_instr *npc;

   npc = ralloc(state->ns, nir_parallel_copy_instr);
   store_ptr(state, npc, pc);

   __clone_instr(state, &npc->instr, &pc->instr);

   nir_foreach_parallel_copy_entry(pc, entry) {
      nir_parallel_copy_entry *nentry;

      nentry = rzalloc(state->ns, nir_parallel_copy_entry);

      __clone_src(state, &nentry->src, &entry->src);
      __clone_dst(state, &nentry->dest, &entry->dest);

      exec_list_push_tail(&npc->entries, &nentry->node);
   }

   return npc;
}

static void *
clone_instr(clone_state *state, const void *ptr)
{
   const nir_instr *instr = ptr;
   switch (instr->type) {
   case nir_instr_type_alu:
      return clone_alu(state, ptr);
   case nir_instr_type_intrinsic:
      return clone_intrinsic(state, ptr);
   case nir_instr_type_load_const:
      return clone_load_const(state, ptr);
   case nir_instr_type_ssa_undef:
      return clone_ssa_undef(state, ptr);
   case nir_instr_type_tex:
      return clone_tex(state, ptr);
   case nir_instr_type_phi:
      return clone_phi(state, ptr);
   case nir_instr_type_jump:
      return clone_jump(state, ptr);
   case nir_instr_type_call:
      return clone_call(state, ptr);
   case nir_instr_type_parallel_copy:
      return clone_parallel_copy(state, ptr);
   default:
      unreachable("bad instr type");
      return NULL;
   }
}

static void
__clone_cf(clone_state *state, nir_cf_node *ncf, const nir_cf_node *cf)
{
   ncf->type = cf->type;
   ncf->parent = clone_ptr(state, cf->parent, clone_cf_node);
}

static void *
clone_block(clone_state *state, const void *ptr)
{
   const nir_block *blk = ptr;
   nir_block *nblk;

   nblk = rzalloc(state->ns, nir_block);
   store_ptr(state, nblk, blk);

   __clone_cf(state, &nblk->cf_node, &blk->cf_node);

   /* clone instructions before successor blocks: */
   exec_list_make_empty(&nblk->instr_list);
   nir_foreach_instr(blk, instr) {
      nir_instr *ninstr = clone_ptr(state, instr, clone_instr);
      exec_list_push_tail(&nblk->instr_list, &ninstr->node);
   }

   nblk->successors[0] = clone_ptr(state, blk->successors[0], clone_block);
   nblk->successors[1] = clone_ptr(state, blk->successors[1], clone_block);
   nblk->predecessors = clone_set(state, nblk, blk->predecessors, clone_block);
   nblk->dom_frontier = _mesa_set_create(nblk, _mesa_hash_pointer,
                                         _mesa_key_pointer_equal);

   return nblk;
}

static void
__clone_block_p2(clone_state *state, nir_block *nblk, const nir_block *blk)
{
   nir_instr *ninstr;

   ninstr = nir_block_first_instr(nblk);
   nir_foreach_instr(blk, instr) {
      nir_add_defs_uses(ninstr);
      ninstr = nir_instr_next(ninstr);
   }
}


static void *
clone_if(clone_state *state, const void *ptr)
{
   const nir_if *i = ptr;
   nir_if *ni;

   ni = ralloc(state->ns, nir_if);
   store_ptr(state, ni, i);

   __clone_cf(state, &ni->cf_node, &i->cf_node);

   __clone_src(state, &ni->condition, &i->condition);
   clone_cf_list(state, &ni->then_list, &i->then_list);
   clone_cf_list(state, &ni->else_list, &i->else_list);

   return ni;
}

static void
__clone_if_p2(clone_state *state, nir_if *ni, const nir_if *i)
{
   nir_update_if_uses(&ni->cf_node);
   __clone_cf_list_p2(state, &ni->then_list, &i->then_list);
   __clone_cf_list_p2(state, &ni->else_list, &i->else_list);
}

static void *
clone_loop(clone_state *state, const void *ptr)
{
   const nir_loop *loop = ptr;
   nir_loop *nloop;

   nloop = ralloc(state->ns, nir_loop);
   store_ptr(state, nloop, loop);

   __clone_cf(state, &nloop->cf_node, &loop->cf_node);

   clone_cf_list(state, &nloop->body, &loop->body);

   return nloop;
}

static void
__clone_loop_p2(clone_state *state, nir_loop *nloop, const nir_loop *loop)
{
   __clone_cf_list_p2(state, &nloop->body, &loop->body);
}

static void *
clone_function_impl(clone_state *state, const void *ptr)
{
   const nir_function_impl *fi = ptr;
   nir_function_impl *nfi;

   nfi = ralloc(state->ns, nir_function_impl);
   store_ptr(state, nfi, fi);

   __clone_cf(state, &nfi->cf_node, &fi->cf_node);

   nfi->overload = clone_ptr(state, fi->overload, clone_function_overload);
   clone_cf_list(state, &nfi->body, &fi->body);
   nfi->end_block = clone_ptr(state, fi->end_block, clone_block);
   clone_var_list(state, &nfi->locals, &fi->locals);

   nfi->num_params = fi->num_params;
   nfi->params = ralloc_array(state->ns, nir_variable *, fi->num_params);
   for (unsigned i = 0; i < fi->num_params; i++) {
      nfi->params[i] = clone_ptr(state, fi->params[i], clone_var);
   }

   nfi->return_var = clone_ptr(state, fi->return_var, clone_var);
   clone_reg_list(state, &nfi->registers, &fi->registers);
   nfi->reg_alloc = fi->reg_alloc;
   nfi->ssa_alloc = fi->ssa_alloc;
   nfi->num_blocks = fi->num_blocks;
   nfi->valid_metadata = 0;

   return nfi;
}

static void
__clone_function_impl_p2(clone_state *state, nir_function_impl *nfi,
                         const nir_function_impl *fi)
{
   __clone_cf_list_p2(state, &nfi->body, &fi->body);
}

static void *
clone_cf_node(clone_state *state, const void *ptr)
{
   const nir_cf_node *cf = ptr;
   switch (cf->type) {
   case nir_cf_node_block:
      return clone_block(state, ptr);
   case nir_cf_node_if:
      return clone_if(state, ptr);
   case nir_cf_node_loop:
      return clone_loop(state, ptr);
   case nir_cf_node_function:
      return clone_function_impl(state, ptr);
   default:
      unreachable("bad cf type");
      return NULL;
   }
}

static void
__clone_cf_node_p2(clone_state *state, nir_cf_node *ncf, const nir_cf_node *cf)
{
   switch (cf->type) {
   case nir_cf_node_block:
      __clone_block_p2(state, nir_cf_node_as_block(ncf), nir_cf_node_as_block(cf));
      break;
   case nir_cf_node_if:
      __clone_if_p2(state, nir_cf_node_as_if(ncf), nir_cf_node_as_if(cf));
      break;
   case nir_cf_node_loop:
      __clone_loop_p2(state, nir_cf_node_as_loop(ncf), nir_cf_node_as_loop(cf));
      break;
   case nir_cf_node_function:
      __clone_function_impl_p2(state, nir_cf_node_as_function(ncf),
                               nir_cf_node_as_function(cf));
      break;
   default:
      unreachable("bad cf type");
      break;
   }
}

static void *
clone_function_overload(clone_state *state, const void *ptr)
{
   const nir_function_overload *fo = ptr;
   nir_function_overload *nfo;

   nfo = ralloc(state->ns, nir_function_overload);
   store_ptr(state, nfo, fo);

   nfo->num_params = fo->num_params;
   nfo->params = ralloc_array(state->ns, nir_parameter, fo->num_params);
   memcpy(nfo->params, fo->params, sizeof(nir_parameter) * fo->num_params);

   nfo->return_type = fo->return_type;
   nfo->impl = clone_ptr(state, fo->impl, clone_function_impl);

   nfo->function = clone_ptr(state, fo->function, clone_function);

   return nfo;
}

static void *
clone_function(clone_state *state, const void *ptr)
{
   const nir_function *fxn = ptr;
   nir_function *nfxn;

   nfxn = ralloc(state->ns, nir_function);
   store_ptr(state, nfxn, fxn);

   exec_list_make_empty(&nfxn->overload_list);
   foreach_list_typed(nir_function_overload, fo, node, &fxn->overload_list) {
      nir_function_overload *nfo = clone_ptr(state, fo, clone_function_overload);
      exec_list_push_tail(&nfxn->overload_list, &nfo->node);
   }

   nfxn->name = ralloc_strdup(nfxn, fxn->name);
   nfxn->shader = state->ns;   /* we could use clone_ptr, but overkill */

   return nfxn;
}

static void *
clone_shader(clone_state *state, const void *ptr)
{
   const nir_shader *s = ptr;
   nir_shader *ns;

   ns = nir_shader_create(state->mem_ctx, s->stage, s->options);
   store_ptr(state, ns, s);
   state->ns = ns;

   clone_var_list(state, &ns->uniforms, &s->uniforms);
   clone_var_list(state, &ns->inputs,   &s->inputs);
   clone_var_list(state, &ns->outputs,  &s->outputs);
   clone_var_list(state, &ns->globals,  &s->globals);
   clone_var_list(state, &ns->system_values, &s->system_values);

   exec_list_make_empty(&ns->functions);
   foreach_list_typed(nir_function, fxn, node, &s->functions) {
      nir_function *nfxn = clone_ptr(state, fxn, clone_function);
      exec_list_push_tail(&ns->functions, &nfxn->node);
   }

   clone_reg_list(state, &ns->registers, &s->registers);

   ns->info = s->info;
   ns->info.name = ralloc_strdup(ns, s->info.name);
   ns->info.label = ralloc_strdup(ns, s->info.label);
   ns->reg_alloc = s->reg_alloc;
   ns->num_inputs = s->num_inputs;
   ns->num_uniforms = s->num_uniforms;
   ns->num_outputs = s->num_outputs;

   return ns;
}

/* second pass for some fixup.. in various cases we can have references
 * to embedded objects that haven't been created yet (like phi src's),
 * so some parts need to be handled on a second pass.
 */
static void
__clone_shader_p2(clone_state *state, nir_shader *ns, const nir_shader *s)
{
   /* resolve ssa srcs: */
   list_for_each_entry(nir_src, nsrc, &state->ssa_src_list, use_link) {
      /* recover the orig src ptr saved in __clone_src(): */
      nir_src *src = (void *)~(uintptr_t)nsrc->ssa;
      nsrc->ssa = clone_ptr(state, src->ssa, NULL);
   }
   /* nir_update_if_uses() and nir_add_defs_uses(): */
   nir_foreach_overload(s, fo) {
      const nir_function_impl *impl = fo->impl;
      nir_function_impl *nimpl = clone_ptr(state, impl, NULL);
      __clone_function_impl_p2(state, nimpl, impl);
   }
}

nir_shader *
nir_shader_clone(void *mem_ctx, const nir_shader *s)
{
   clone_state state;
   nir_shader *ns;

   init_clone_state(&state, mem_ctx);
   ns = clone_ptr(&state, s, clone_shader);
   __clone_shader_p2(&state, ns, s);
   free_clone_state(&state);

   return ns;
}
