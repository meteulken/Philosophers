/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocCollector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:23:53 by mulken            #+#    #+#             */
/*   Updated: 2024/01/28 14:13:59 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mallocCollector.h"
#include <stdlib.h>
#include <unistd.h>

t_mallocCollector	*malloc_start(void)
{
	t_mallocCollector	*mc;

	mc = (t_mallocCollector *)malloc(sizeof(t_mallocCollector));
	if (mc != NULL)
	{
		mc->new_malloc = NULL;
		mc->next = NULL;
	}
	return (mc);
}

void	*new_malloc(t_mallocCollector *mc, size_t size)
{
	t_mallocCollector	*new_node;
	void				*ptr;

	if (mc == NULL)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		write(1, "| new_malloc allocate error >:|       |\n", 40);
		end_malloc(mc);
		//exit(1);
	}
	new_node = (t_mallocCollector *)malloc(sizeof(t_mallocCollector));
	if (!new_node)
	{
		write(1, "| new_malloc allocate error >:|       |\n", 40);
		free(ptr);
		end_malloc(mc);
		//exit(1);
	}
	new_node->new_malloc = ptr;
	new_node->next = mc->next;
	mc->next = new_node;
	return (ptr);
}

void	delete_malloc(t_mallocCollector *mc, void *ptr_to_delete)
{
	t_mallocCollector	*prev;
	t_mallocCollector	*current;

	if (mc == NULL || ptr_to_delete == NULL)
		return ;
	prev = NULL;
	current = mc;
	while (current != NULL && current->new_malloc != ptr_to_delete)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		if (prev == NULL)
			mc = current->next;
		else
			prev->next = current->next;
		if (current->new_malloc)
			free(current->new_malloc);
		free(current);
	}
}

void	end_malloc(t_mallocCollector *mc)
{
	if (!mc)
		return ;
	if (mc->next != NULL)
		end_malloc(mc->next);
	if (mc->new_malloc)
		free(mc->new_malloc);
	free(mc);
}