/**
 * \file frontend.c
 * AGPGART module frontend
 * \version 0.99
 * 
 * \author Jeff Hartmann
 */

/*
 * Copyright (C) 1999 Jeff Hartmann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mman.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/agp_backend.h>
#include <linux/agpgart.h>
#include <asm/uaccess.h>

#include "agp.h"

/** Global AGP frontend data. */
static struct agp_front_data agp_fe;

/**
 * Find an agp_memory structure by its allocation tag.
 *
 * \param key allocation tag.
 * \return pointer to the agp_memory on success or NULL on failure.
 *
 * Walks trhough the agp_controller::pool list until finding a matching key.
 */
static agp_memory *agp_find_mem_by_key(int key)
{
	agp_memory *curr;

	if (agp_fe.current_controller == NULL) {
		return NULL;
	}
	curr = agp_fe.current_controller->pool;

	while (curr != NULL) {
		if (curr->key == key) {
			return curr;
		}
		curr = curr->next;
	}

	return NULL;
}

/**
 * Removes an entry from its memory pool.
 *
 * \param temp pointer to the agp_memory structure.
 * 
 * Unlinks the entry from the doubly linked list.
 */
static void agp_remove_from_pool(agp_memory * temp)
{
	agp_memory *prev;
	agp_memory *next;

	/* Check to see if this is even in the memory pool */

	if (agp_find_mem_by_key(temp->key) != NULL) {
		next = temp->next;
		prev = temp->prev;

		if (prev != NULL) {
			prev->next = next;
			if (next != NULL) {
				next->prev = prev;
			}
		} else {
			/* This is the first item on the list */
			if (next != NULL) {
				next->prev = NULL;
			}
			agp_fe.current_controller->pool = next;
		}
	}
}

/**
 * \name Routines for managing each client's segment list
 *
 * These routines handle adding and removing segments to each authorized
 * client.
 */
/*@{*/

/**
 * Find a segment in the client information.
 *
 * \param client client information.
 * \param offset offset.
 * \param size size.
 * \param page_prot memory protection flags .
 * \return pointer to the segment private data on success or NULL on failure.
 *
 * Walks through every segment in \p client until find one with a macthing
 * offset, size and memory protection flags.
 */
static agp_segment_priv *agp_find_seg_in_client(const agp_client * client,
						unsigned long offset,
					    int size, pgprot_t page_prot)
{
	agp_segment_priv *seg;
	int num_segments, pg_start, pg_count, i;

	pg_start = offset / 4096;
	pg_count = size / 4096;
	seg = *(client->segments);
	num_segments = client->num_segments;

	for (i = 0; i < client->num_segments; i++) {
		if ((seg[i].pg_start == pg_start) &&
		    (seg[i].pg_count == pg_count) &&
		    (pgprot_val(seg[i].prot) == pgprot_val(page_prot))) {
			return seg + i;
		}
	}

	return NULL;
}

/**
 * Remove the segment list from the client data.
 *
 * \param client client information.
 *
 * Frees the agp_client::segments and what it's pointed by it if not null.
 */
static void agp_remove_seg_from_client(agp_client * client)
{
	if (client->segments != NULL) {
		if (*(client->segments) != NULL) {
			kfree(*(client->segments));
		}
		kfree(client->segments);
	}
}

/**
 * Add a segment list to the client data.
 *
 * \param client client information.
 * \param seg segment list.
 * \param num_segments number of segments in the list.
 *
 * Updates agp_client::segments, calling agp_remove_seg_from_client() if there
 * is a previous value.
 */
static void agp_add_seg_to_client(agp_client * client,
			       agp_segment_priv ** seg, int num_segments)
{
	agp_segment_priv **prev_seg;

	prev_seg = client->segments;

	if (prev_seg != NULL) {
		agp_remove_seg_from_client(client);
	}
	client->num_segments = num_segments;
	client->segments = seg;
}

/**
 * Originally taken from linux/mm/mmap.c from the array
 * protection_map.
 * 
 * The original really should be exported to modules, or 
 * some routine which does the conversion for you 
 */
static const pgprot_t my_protect_map[16] =
{
	__P000, __P001, __P010, __P011, __P100, __P101, __P110, __P111,
	__S000, __S001, __S010, __S011, __S100, __S101, __S110, __S111
};

/** 
 * Convert the mmap() memory protection flags into a pgprot_t.
 * 
 * \param prot memory protection flags as used by mmap().
 * \return a pgprot_t structure.
 */
static pgprot_t agp_convert_mmap_flags(int prot)
{
#define _trans(x,bit1,bit2) \
((bit1==bit2)?(x&bit1):(x&bit1)?bit2:0)

	unsigned long prot_bits;
	pgprot_t temp;

	prot_bits = _trans(prot, PROT_READ, VM_READ) |
	    _trans(prot, PROT_WRITE, VM_WRITE) |
	    _trans(prot, PROT_EXEC, VM_EXEC);

	prot_bits |= VM_SHARED;

	temp = my_protect_map[prot_bits & 0x0000000f];

	return temp;
}

/** 
 * Create a segment.
 * 
 * \param client client information.
 * \param region memory region.
 * \return zero on success or a negative number on failure.
 *
 * Allocates a new segment list to hold the segments in \p region, copies the
 * segments, and adds it to the client via agp_add_seg_to_client().
 */
static int agp_create_segment(agp_client * client, agp_region * region)
{
	agp_segment_priv **ret_seg;
	agp_segment_priv *seg;
	agp_segment *user_seg;
	int i;

	seg = kmalloc((sizeof(agp_segment_priv) * region->seg_count),
		      GFP_KERNEL);
	if (seg == NULL) {
		kfree(region->seg_list);
		return -ENOMEM;
	}
	memset(seg, 0, (sizeof(agp_segment_priv) * region->seg_count));
	user_seg = region->seg_list;

	for (i = 0; i < region->seg_count; i++) {
		seg[i].pg_start = user_seg[i].pg_start;
		seg[i].pg_count = user_seg[i].pg_count;
		seg[i].prot = agp_convert_mmap_flags(user_seg[i].prot);
	}
	ret_seg = kmalloc(sizeof(void *), GFP_KERNEL);
	if (ret_seg == NULL) {
		kfree(region->seg_list);
		kfree(seg);
		return -ENOMEM;
	}
	*ret_seg = seg;
	kfree(region->seg_list);
	agp_add_seg_to_client(client, ret_seg, region->seg_count);
	return 0;
}

/*@}*/


/**
 * Insert memory in the current controller pool.
 * 
 * This function must only be called when current_controller != NULL 
 * 
 * \param temp memory to insert.
 * 
 * Links \p temp into agp_front_data::pool.
 */
static void agp_insert_into_pool(agp_memory * temp)
{
	agp_memory *prev;

	prev = agp_fe.current_controller->pool;

	if (prev != NULL) {
		prev->prev = temp;
		temp->next = prev;
	}
	agp_fe.current_controller->pool = temp;
}


/** \name File private list routines */
/*@{*/

/**
 * Find the file private data for the given process id.
 *
 * \param pid process id.
 * \return pointer to the file private data on success or NULL on failure.
 * 
 * Searches for the given process id on the agp_front_data::file_priv_list.
 */
agp_file_private *agp_find_private(pid_t pid)
{
	agp_file_private *curr;

	curr = agp_fe.file_priv_list;

	while (curr != NULL) {
		if (curr->my_pid == pid) {
			return curr;
		}
		curr = curr->next;
	}

	return NULL;
}

/** 
 * Insert the file private data.
 *
 * \param priv file private data.
 *
 * Inserts \p priv into agp_front_data::file_priv_list.
 */
void agp_insert_file_private(agp_file_private * priv)
{
	agp_file_private *prev;

	prev = agp_fe.file_priv_list;

	if (prev != NULL) {
		prev->prev = priv;
	}
	priv->next = prev;
	agp_fe.file_priv_list = priv;
}

/** 
 * Remove the file private data.
 *
 * \param priv file private data.
 *
 * Removes \p priv from agp_front_data::file_priv_list.
 */
void agp_remove_file_private(agp_file_private * priv)
{
	agp_file_private *next;
	agp_file_private *prev;

	next = priv->next;
	prev = priv->prev;

	if (prev != NULL) {
		prev->next = next;

		if (next != NULL) {
			next->prev = prev;
		}
	} else {
		if (next != NULL) {
			next->prev = NULL;
		}
		agp_fe.file_priv_list = next;
	}
}

/*@}*/


/**
 * \name Wrappers for agp_free_memory() and agp_allocate_memory()
 */
/*@{*/

/**
 * Wrapper for agp_free_memory().
 *
 * Makes sure that internal lists are kept updated by calling
 * agp_remove_from_pool().
 */
static void agp_free_memory_wrap(agp_memory * memory)
{
	agp_remove_from_pool(memory);
	agp_free_memory(memory);
}

/**
 * Wrapper for agp_allocate_memory().
 *
 * Makes sure that internal lists are kept updated by calling
 * agp_insert_into_pool().
 */
static agp_memory *agp_allocate_memory_wrap(size_t pg_count, u32 type)
{
	agp_memory *memory;

	memory = agp_allocate_memory(pg_count, type);
   	printk(KERN_DEBUG "agp_allocate_memory: %p\n", memory);
	if (memory == NULL) {
		return NULL;
	}
	agp_insert_into_pool(memory);
	return memory;
}

/*@}*/

/**
 * \name Routines for managing the list of controllers
 * 
 * These routines manage the current controller, and the list of controllers
 */

/**
 * Find controller by process id.
 *
 * \param id process id of the controller.Insert
 * \return pointer to the controller on success or NULL on failure.
 *
 * Searches for the given process id in agp_front_data:controllers list.
 */
static agp_controller *agp_find_controller_by_pid(pid_t id)
{
	agp_controller *controller;

	controller = agp_fe.controllers;

	while (controller != NULL) {
		if (controller->pid == id) {
			return controller;
		}
		controller = controller->next;
	}

	return NULL;
}

/**
 * Create a controller structure.
 *
 * \param id process id of the new controller.
 * \return pointer to the agp_controller structure on success, or NULL on failure.
 * 
 * Allocate and initialize an agp_controller structure.
 */
static agp_controller *agp_create_controller(pid_t id)
{
	agp_controller *controller;

	controller = kmalloc(sizeof(agp_controller), GFP_KERNEL);

	if (controller == NULL) {
		return NULL;
	}
	memset(controller, 0, sizeof(agp_controller));
	controller->pid = id;

	return controller;
}

/** 
 * Insert a controller into the frontend data.
 *
 * \param controller controller information.
 * \return always zero.
 *
 * Inserts \p controller into agp_front_data::controllers.
 */
static int agp_insert_controller(agp_controller * controller)
{
	agp_controller *prev_controller;

	prev_controller = agp_fe.controllers;
	controller->next = prev_controller;

	if (prev_controller != NULL) {
		prev_controller->prev = controller;
	}
	agp_fe.controllers = controller;

	return 0;
}

/**
 * Remove all clients associated with a given controller.
 *
 * For each client in \p controller removes its segments, clears the valid and
 * client flags from the file private data, and frees the client structure
 * itself.
 */ 
static void agp_remove_all_clients(agp_controller * controller)
{
	agp_client *client;
	agp_client *temp;

	client = controller->clients;

	while (client) {
		agp_file_private *priv;

		temp = client;
		agp_remove_seg_from_client(temp);
		priv = agp_find_private(temp->pid);

		if (priv != NULL) {
			clear_bit(AGP_FF_IS_VALID, &priv->access_flags);
			clear_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		}
		client = client->next;
		kfree(temp);
	}
}

/**
 * Remove all memory associated with a given controller.
 *
 * Calls agp_free_memory_wrap() for each memory entry in agp_controller::pool.
 */
static void agp_remove_all_memory(agp_controller * controller)
{
	agp_memory *memory;
	agp_memory *temp;

	memory = controller->pool;

	while (memory) {
		temp = memory;
		memory = memory->next;
		agp_free_memory_wrap(temp);
	}
}

/**
 * Remove a controller.
 *
 * \param controller controller to remove.
 * \return always zero.
 * 
 * Unlinks the controller from agp_front_data::controllers and frees the
 * controller structure. If removing the current controller additionally
 * releases the backend and unsets the current controller.
 */
static int agp_remove_controller(agp_controller * controller)
{
	agp_controller *prev_controller;
	agp_controller *next_controller;

	prev_controller = controller->prev;
	next_controller = controller->next;

	if (prev_controller != NULL) {
		prev_controller->next = next_controller;
		if (next_controller != NULL) {
			next_controller->prev = prev_controller;
		}
	} else {
		if (next_controller != NULL) {
			next_controller->prev = NULL;
		}
		agp_fe.controllers = next_controller;
	}

	agp_remove_all_memory(controller);
	agp_remove_all_clients(controller);

	if (agp_fe.current_controller == controller) {
		agp_fe.current_controller = NULL;
		agp_fe.backend_acquired = FALSE;
		agp_backend_release();
	}
	kfree(controller);
	return 0;
}

/**
 * Make a controller current.
 *
 * \param controller controller to make current.
 *
 * Sets the valid and client flags for each client file and points the current
 * controller, agp_front_data::current_controller, to \p controller.
 */
static void agp_controller_make_current(agp_controller * controller)
{
	agp_client *clients;

	clients = controller->clients;

	while (clients != NULL) {
		agp_file_private *priv;

		priv = agp_find_private(clients->pid);

		if (priv != NULL) {
			set_bit(AGP_FF_IS_VALID, &priv->access_flags);
			set_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		}
		clients = clients->next;
	}

	agp_fe.current_controller = controller;
}

/** 
 * Release the current controller.
 *
 * \param controller controller.
 * \param controller_priv controller file private data.
 *
 * Clears the valid flags in the controller file and in each client file.
 * Unsets the current controller and releases the backend.
 */
static void agp_controller_release_current(agp_controller * controller,
				      agp_file_private * controller_priv)
{
	agp_client *clients;

	clear_bit(AGP_FF_IS_VALID, &controller_priv->access_flags);
	clients = controller->clients;

	while (clients != NULL) {
		agp_file_private *priv;

		priv = agp_find_private(clients->pid);

		if (priv != NULL) {
			clear_bit(AGP_FF_IS_VALID, &priv->access_flags);
		}
		clients = clients->next;
	}

	agp_fe.current_controller = NULL;
	agp_fe.used_by_controller = FALSE;
	agp_backend_release();
}

/*@}*/


/**
 * \name Routines for managing client lists
 *
 * These routines are for managing the list of authorized clients.
 */
/*@{*/

/**
 * Find a client in a controller with a given process id.
 *
 * \param controller controller to search the client on.
 * \param id clinet process id.
 * \return pointer to the client structure on success or NULL otherwise.
 * 
 * Search the given process id in agp_contoller::clients.
 */
static agp_client *agp_find_client_in_controller(agp_controller * controller,
						 pid_t id)
{
	agp_client *client;

	if (controller == NULL) {
		return NULL;
	}
	client = controller->clients;

	while (client != NULL) {
		if (client->pid == id) {
			return client;
		}
		client = client->next;
	}

	return NULL;
}

/**
 * Find the controller to which the client belongs.
 *
 * \param id client process id.
 * \return pointer to the controller structure associated with the client on success, or NULL on failure.
 *
 * Search the controller by successive calls to agp_find_client_in_controller()
 * for each controller until a match is found.
 */
static agp_controller *agp_find_controller_for_client(pid_t id)
{
	agp_controller *controller;

	controller = agp_fe.controllers;

	while (controller != NULL) {
		if ((agp_find_client_in_controller(controller, id)) != NULL) {
			return controller;
		}
		controller = controller->next;
	}

	return NULL;
}

/**
 * Find the client with the given process id.
 *
 * \param id client process id.
 * \return pointer to the client structure on success or NULL on failure.
 * 
 * Search the client in the current controller.
 */
static agp_client *agp_find_client_by_pid(pid_t id)
{
	agp_client *temp;

	if (agp_fe.current_controller == NULL) {
		return NULL;
	}
	temp = agp_find_client_in_controller(agp_fe.current_controller, id);
	return temp;
}

/**
 * Insert client into the current controller.
 *
 * \param client client information.
 * 
 * Insert \p client into the agp_controller::clients list of the current
 * controller.
 */
static void agp_insert_client(agp_client * client)
{
	agp_client *prev_client;

	prev_client = agp_fe.current_controller->clients;
	client->next = prev_client;

	if (prev_client != NULL) {
		prev_client->prev = client;
	}
	agp_fe.current_controller->clients = client;
	agp_fe.current_controller->num_clients++;
}

/**
 * Create a client structure.
 *
 * \param id client process id.
 * \return a pointer to an agp_client structure.
 *
 * Allocate and initialize an agp_client structure and inserts into the current
 * controller.
 */
static agp_client *agp_create_client(pid_t id)
{
	agp_client *new_client;

	new_client = kmalloc(sizeof(agp_client), GFP_KERNEL);

	if (new_client == NULL) {
		return NULL;
	}
	memset(new_client, 0, sizeof(agp_client));
	new_client->pid = id;
	agp_insert_client(new_client);
	return new_client;
}

/**
 * Remove client.
 *
 * \param id client process id.
 *
 * Find the controller to which the client belongs, then the client data, and
 * unlinks it from its list. Removes the segments from the client and finally
 * frees the client structure itself.
 */
static int agp_remove_client(pid_t id)
{
	agp_client *client;
	agp_client *prev_client;
	agp_client *next_client;
	agp_controller *controller;

	controller = agp_find_controller_for_client(id);

	if (controller == NULL) {
		return -EINVAL;
	}
	client = agp_find_client_in_controller(controller, id);

	if (client == NULL) {
		return -EINVAL;
	}
	prev_client = client->prev;
	next_client = client->next;

	if (prev_client != NULL) {
		prev_client->next = next_client;
		if (next_client != NULL) {
			next_client->prev = prev_client;
		}
	} else {
		if (next_client != NULL) {
			next_client->prev = NULL;
		}
		controller->clients = next_client;
	}

	controller->num_clients--;
	agp_remove_seg_from_client(client);
	kfree(client);
	return 0;
}

/*@}*/


/** \name File Operations */
/*@{*/

/**
 * Memory mapping.
 *
 * \param file file pointer.
 * \param vma virtual memory area.
 *
 * Holds the AGP lock and tests that the valid flag is set on the file private
 * data.
 * 
 * If it's a client then verifies the area fits the current aperture, finds the
 * segment matching the given area and remaps it.
 *
 * If it's a controller then verifies the area size matches the aperture size
 * and remaps it.
 */
static int agp_mmap(struct file *file, struct vm_area_struct *vma)
{
	int size;
	int current_size;
	unsigned long offset;
	agp_client *client;
	agp_file_private *priv = (agp_file_private *) file->private_data;
	agp_kern_info kerninfo;

	AGP_LOCK();

	if (agp_fe.backend_acquired != TRUE) {
		AGP_UNLOCK();
		return -EPERM;
	}
	if (!(test_bit(AGP_FF_IS_VALID, &priv->access_flags))) {
		AGP_UNLOCK();
		return -EPERM;
	}
	agp_copy_info(&kerninfo);
	size = vma->vm_end - vma->vm_start;
	current_size = kerninfo.aper_size;
	current_size = current_size * 0x100000;
	offset = vma->vm_pgoff << PAGE_SHIFT;

	if (test_bit(AGP_FF_IS_CLIENT, &priv->access_flags)) {
		if ((size + offset) > current_size) {
			AGP_UNLOCK();
			return -EINVAL;
		}
		client = agp_find_client_by_pid(current->pid);

		if (client == NULL) {
			AGP_UNLOCK();
			return -EPERM;
		}
		if (!agp_find_seg_in_client(client, offset,
					    size, vma->vm_page_prot)) {
			AGP_UNLOCK();
			return -EINVAL;
		}
		if (remap_page_range(vma, vma->vm_start,
				     (kerninfo.aper_base + offset),
				     size, vma->vm_page_prot)) {
			AGP_UNLOCK();
			return -EAGAIN;
		}
		AGP_UNLOCK();
		return 0;
	}
	if (test_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags)) {
		if (size != current_size) {
			AGP_UNLOCK();
			return -EINVAL;
		}
		if (remap_page_range(vma, vma->vm_start, kerninfo.aper_base,
				     size, vma->vm_page_prot)) {
			AGP_UNLOCK();
			return -EAGAIN;
		}
		AGP_UNLOCK();
		return 0;
	}
	AGP_UNLOCK();
	return -EPERM;
}

/**
 * Release the device.
 *
 * \param inode device inode.
 * \param file file pointer.
 * \return zero on success or a negative number on failure.
 * 
 * If it's a controller then finds its data structure and removes it. If it's
 * the current controller then additionally calls
 * agp_controller_release_current().
 * 
 * If it's a client then simply remove the client.
 *
 * The AGP lock is held during the function call and the file private data is
 * freed before returning.
 */
static int agp_release(struct inode *inode, struct file *file)
{
	agp_file_private *priv = (agp_file_private *) file->private_data;

	AGP_LOCK();

	if (test_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags)) {
		agp_controller *controller;

		controller = agp_find_controller_by_pid(priv->my_pid);

		if (controller != NULL) {
			if (controller == agp_fe.current_controller) {
				agp_controller_release_current(controller,
							       priv);
			}
			agp_remove_controller(controller);
		}
	}
	if (test_bit(AGP_FF_IS_CLIENT, &priv->access_flags)) {
		agp_remove_client(priv->my_pid);
	}
	agp_remove_file_private(priv);
	kfree(priv);
	AGP_UNLOCK();
	return 0;
}

/**
 * Open the device.
 *
 * \param inode device inode.
 * \param file file pointer.
 * \return zero on success or a negative number on failure.
 * 
 * Allocate and create an agp_file_private structure for the file private data,
 * and sets the client allow flag. If the user or the suid is zero then sets the
 * <i>controller allow</i> flag too.
 *
 * If there is a client with the current proccess id then set the \e client and
 * \e valid flags.
 * 
 * The AGP lock is held during the function call.
 */
static int agp_open(struct inode *inode, struct file *file)
{
	int minor = minor(inode->i_rdev);
	agp_file_private *priv;
	agp_client *client;
	int rc = -ENXIO;

	AGP_LOCK();

	if (minor != AGPGART_MINOR)
		goto err_out;

	priv = kmalloc(sizeof(agp_file_private), GFP_KERNEL);
	if (priv == NULL)
		goto err_out_nomem;

	memset(priv, 0, sizeof(agp_file_private));
	set_bit(AGP_FF_ALLOW_CLIENT, &priv->access_flags);
	priv->my_pid = current->pid;

	if ((current->uid == 0) || (current->suid == 0)) {
		/* Root priv, can be controller */
		set_bit(AGP_FF_ALLOW_CONTROLLER, &priv->access_flags);
	}
	client = agp_find_client_by_pid(current->pid);

	if (client != NULL) {
		set_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		set_bit(AGP_FF_IS_VALID, &priv->access_flags);
	}
	file->private_data = (void *) priv;
	agp_insert_file_private(priv);
	AGP_UNLOCK();
	return 0;

err_out_nomem:
	rc = -ENOMEM;
err_out:
	AGP_UNLOCK();
	return rc;
}

/** No-op. */
static ssize_t agp_read(struct file *file, char *buf,
			size_t count, loff_t * ppos)
{
	return -EINVAL;
}

/** No-op. */
static ssize_t agp_write(struct file *file, const char *buf,
			 size_t count, loff_t * ppos)
{
	return -EINVAL;
}

/**
 * Information ioctl.
 *
 * \param priv file private data.
 * \param arg user argument pointing to an agp_info structure where the AGP
 * information will be copied.
 * \return zero on success or a negative number on failure.
 *
 * Calls agp_copy_info(), transfers the information into an agp_info structure
 * and copies into user space.
 */
static int agpioc_info_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_info userinfo;
	agp_kern_info kerninfo;

	agp_copy_info(&kerninfo);

	userinfo.version.major = kerninfo.version.major;
	userinfo.version.minor = kerninfo.version.minor;
	userinfo.bridge_id = kerninfo.device->vendor |
	    (kerninfo.device->device << 16);
	userinfo.agp_mode = kerninfo.mode;
	userinfo.aper_base = kerninfo.aper_base;
	userinfo.aper_size = kerninfo.aper_size;
	userinfo.pg_total = userinfo.pg_system = kerninfo.max_memory;
	userinfo.pg_used = kerninfo.current_memory;

	if (copy_to_user((void *) arg, &userinfo, sizeof(agp_info))) {
		return -EFAULT;
	}
	return 0;
}

/**
 * AGP acquire ioctl.
 *
 * \param priv file private data.
 * \param arg user argument. Not referenced.
 * \return zero on success or a negative number on failure.
 *
 * Verifies the allow controller flag is set and that no other controller has
 * acquired the device, and acquires it. 
 *
 * If there is a controller with a given process id the make it current,
 * otherwsie create a new controller, insert it, and make it current. Sets the
 * controller and valid flags.
 */
static int agpioc_acquire_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_controller *controller;
	if (!(test_bit(AGP_FF_ALLOW_CONTROLLER, &priv->access_flags))) {
		return -EPERM;
	}
	if (agp_fe.current_controller != NULL) {
		return -EBUSY;
	}
	if ((agp_backend_acquire()) == 0) {
		agp_fe.backend_acquired = TRUE;
	} else {
		return -EBUSY;
	}

	controller = agp_find_controller_by_pid(priv->my_pid);

	if (controller != NULL) {
		agp_controller_make_current(controller);
	} else {
		controller = agp_create_controller(priv->my_pid);

		if (controller == NULL) {
			agp_fe.backend_acquired = FALSE;
			agp_backend_release();
			return -ENOMEM;
		}
		agp_insert_controller(controller);
		agp_controller_make_current(controller);
	}

	set_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags);
	set_bit(AGP_FF_IS_VALID, &priv->access_flags);
	return 0;
}

/**
 * AGP release ioctl.
 *
 * \param priv file private data.
 * \param arg user argument. Not referenced.
 * \return zero on success or a negative number on failure.
 *
 * Wrapper around agp_controller_release_current().
 */
static int agpioc_release_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_controller_release_current(agp_fe.current_controller, priv);
	return 0;
}

/**
 * AGP setup ioctl.
 *
 * \param priv file private data.
 * \param arg user argument, pointing to an agp_setup structure.
 * \return zero on success or a negative number on failure.
 *
 * Wrapper around agp_enable().
 */
static int agpioc_setup_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_setup mode;

	if (copy_from_user(&mode, (void *) arg, sizeof(agp_setup))) {
		return -EFAULT;
	}
	agp_enable(mode.agp_mode);
	return 0;
}

/**
 * AGP reserve ioctl.
 *
 * \param priv file private data.
 * \param arg user argument, pointing to an agp_region structure.
 * \return zero on success or a negative number on failure.
 *
 * Find the client with the given process id. If agp_region::seg_count is zero
 * then remove the client if any, after setting the client and the valid flags.
 * Otherwise create a new segment via agp_create_segment(), creating a new
 * client if necessary.
 */
static int agpioc_reserve_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_region reserve;
	agp_client *client;
	agp_file_private *client_priv;


	if (copy_from_user(&reserve, (void *) arg, sizeof(agp_region))) {
		return -EFAULT;
	}
	if ((unsigned) reserve.seg_count >= ~0U/sizeof(agp_segment))
		return -EFAULT;

	client = agp_find_client_by_pid(reserve.pid);

	if (reserve.seg_count == 0) {
		/* remove a client */
		client_priv = agp_find_private(reserve.pid);

		if (client_priv != NULL) {
			set_bit(AGP_FF_IS_CLIENT,
				&client_priv->access_flags);
			set_bit(AGP_FF_IS_VALID,
				&client_priv->access_flags);
		}
		if (client == NULL) {
			/* client is already removed */
			return 0;
		}
		return agp_remove_client(reserve.pid);
	} else {
		agp_segment *segment;

		if (reserve.seg_count >= 16384)
			return -EINVAL;
			
		segment = kmalloc((sizeof(agp_segment) * reserve.seg_count),
				  GFP_KERNEL);

		if (segment == NULL) {
			return -ENOMEM;
		}
		if (copy_from_user(segment, (void *) reserve.seg_list,
				   sizeof(agp_segment) * reserve.seg_count)) {
			kfree(segment);
			return -EFAULT;
		}
		reserve.seg_list = segment;

		if (client == NULL) {
			/* Create the client and add the segment */
			client = agp_create_client(reserve.pid);

			if (client == NULL) {
				kfree(segment);
				return -ENOMEM;
			}
			client_priv = agp_find_private(reserve.pid);

			if (client_priv != NULL) {
				set_bit(AGP_FF_IS_CLIENT,
					&client_priv->access_flags);
				set_bit(AGP_FF_IS_VALID,
					&client_priv->access_flags);
			}
			return agp_create_segment(client, &reserve);
		} else {
			return agp_create_segment(client, &reserve);
		}
	}
	/* Will never really happen */
	return -EINVAL;
}

/** No-op. This function is not currently implemented */
static int agpioc_protect_wrap(agp_file_private * priv, unsigned long arg)
{
	/* This function is not currently implemented */
	return -EINVAL;
}

/**
 * Memory allocation ioctl.
 *
 * \param priv file private data.
 * \param arg user argument, pointing to an agp_allocate structure.
 * \return zero on success or a negative number on failure.
 *
 * Wrapper around agp_allocate_memory_wrap().
 */
static int agpioc_allocate_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_memory *memory;
	agp_allocate alloc;

	if (copy_from_user(&alloc, (void *) arg, sizeof(agp_allocate))) {
		return -EFAULT;
	}
	memory = agp_allocate_memory_wrap(alloc.pg_count, alloc.type);

	if (memory == NULL) {
		return -ENOMEM;
	}
	alloc.key = memory->key;
	alloc.physical = memory->physical;

	if (copy_to_user((void *) arg, &alloc, sizeof(agp_allocate))) {
		agp_free_memory_wrap(memory);
		return -EFAULT;
	}
	return 0;
}

/**
 * Memory deallocation ioctl.
 *
 * \param priv file private data.
 * \param arg allocation tag.
 * \return zero on success or a negative number on failure.
 *
 * Wrapper around agp_free_memory_wrap(), using the allocation tag as
 * reference.
 */
static int agpioc_deallocate_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_memory *memory;

	memory = agp_find_mem_by_key((int) arg);

	if (memory == NULL) {
		return -EINVAL;
	}
	agp_free_memory_wrap(memory);
	return 0;
}

/**
 * Memory binding ioctl.
 *
 * \param priv file private data.
 * \param arg allocation tag.
 * \return zero on success or a negative number on failure.
 *
 * Wrapper around agp_bind_memory(), using the allocation tag as
 * reference.
 */
static int agpioc_bind_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_bind bind_info;
	agp_memory *memory;

	if (copy_from_user(&bind_info, (void *) arg, sizeof(agp_bind))) {
		return -EFAULT;
	}
	memory = agp_find_mem_by_key(bind_info.key);

	if (memory == NULL) {
		return -EINVAL;
	}
	return agp_bind_memory(memory, bind_info.pg_start);
}

/**
 * Memory unbinding ioctl.
 *
 * \param priv file private data.
 * \param arg allocation tag.
 * \return zero on success or a negative number on failure.
 *
 * Wrapper around agp_unbind_memory(), using the allocation tag as
 * reference.
 */
static int agpioc_unbind_wrap(agp_file_private * priv, unsigned long arg)
{
	agp_memory *memory;
	agp_unbind unbind;

	if (copy_from_user(&unbind, (void *) arg, sizeof(agp_unbind))) {
		return -EFAULT;
	}
	memory = agp_find_mem_by_key(unbind.key);

	if (memory == NULL) {
		return -EINVAL;
	}
	return agp_unbind_memory(memory);
}


/**
 * Ioctl handler.
 *
 * \param inode device inode.
 * \param file file pointer.
 * \param cmd command.
 * \param arg allocation tag.
 * \return zero on success or a negative number on failure.
 *
 * Locks the AGP device, makes some sanity checks, and dispatches to one of the
 * agpioc_* functions above according with the value of \p cmd.
 */
static int agp_ioctl(struct inode *inode, struct file *file,
		     unsigned int cmd, unsigned long arg)
{
	agp_file_private *curr_priv = (agp_file_private *) file->private_data;
	int ret_val = -ENOTTY;

	AGP_LOCK();

	if ((agp_fe.current_controller == NULL) &&
	    (cmd != AGPIOC_ACQUIRE)) {
		ret_val = -EINVAL;
	   	goto ioctl_out;
	}
	if ((agp_fe.backend_acquired != TRUE) &&
	    (cmd != AGPIOC_ACQUIRE)) {
		ret_val = -EBUSY;
	   	goto ioctl_out;
	}
	if (cmd != AGPIOC_ACQUIRE) {
		if (!(test_bit(AGP_FF_IS_CONTROLLER,
			       &curr_priv->access_flags))) {
			ret_val = -EPERM;
		   	goto ioctl_out;
		}
		/* Use the original pid of the controller,
		 * in case it's threaded */

		if (agp_fe.current_controller->pid != curr_priv->my_pid) {
			ret_val = -EBUSY;
		   	goto ioctl_out;
		}
	}
	switch (cmd) {
	case AGPIOC_INFO:
		{
			ret_val = agpioc_info_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_ACQUIRE:
		{
			ret_val = agpioc_acquire_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_RELEASE:
		{
			ret_val = agpioc_release_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_SETUP:
		{
			ret_val = agpioc_setup_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_RESERVE:
		{
			ret_val = agpioc_reserve_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_PROTECT:
		{
			ret_val = agpioc_protect_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_ALLOCATE:
		{
			ret_val = agpioc_allocate_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_DEALLOCATE:
		{
			ret_val = agpioc_deallocate_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_BIND:
		{
			ret_val = agpioc_bind_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	case AGPIOC_UNBIND:
		{
			ret_val = agpioc_unbind_wrap(curr_priv, arg);
		   	goto ioctl_out;
		}
	}
   
ioctl_out:
	AGP_UNLOCK();
	return ret_val;
}

/** File operations structure. */
static struct file_operations agp_fops =
{
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.read		= agp_read,
	.write		= agp_write,
	.ioctl		= agp_ioctl,
	.mmap		= agp_mmap,
	.open		= agp_open,
	.release	= agp_release,
};

/*@}*/

/** Misc device structure. */
static struct miscdevice agp_miscdev =
{
	AGPGART_MINOR,
	AGPGART_MODULE_NAME,
	&agp_fops
};

/** 
 * Frontend initialization. 
 *
 * Registers agp_miscdev.
 */
int __init agp_frontend_initialize(void)
{
	memset(&agp_fe, 0, sizeof(struct agp_front_data));
	AGP_LOCK_INIT();

	if (misc_register(&agp_miscdev)) {
		printk(KERN_ERR PFX "unable to get minor: %d\n", AGPGART_MINOR);
		return -EIO;
	}
	return 0;
}

/** 
 * Frontend cleanup. 
 * 
 * Unregisters agp_miscdev.
 */
void __exit agp_frontend_cleanup(void)
{
	misc_deregister(&agp_miscdev);
}

