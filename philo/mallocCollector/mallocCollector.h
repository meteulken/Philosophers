/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocCollector.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 02:00:13 by mulken            #+#    #+#             */
/*   Updated: 2024/02/03 02:00:14 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOCCOLLECTOR_H
# define MALLOCCOLLECTOR_H

# include <stdlib.h>

typedef struct s_mallocCollector
{
	void						*new_malloc;
	struct s_mallocCollector	*next;
}	t_mallocCollector;

t_mallocCollector	*malloc_start(void);
void				*new_malloc(t_mallocCollector *mc, size_t size);
void				delete_malloc(t_mallocCollector *mc, void *ptr_to_delete);
void				end_malloc(t_mallocCollector *mc);

#endif