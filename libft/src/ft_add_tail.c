/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 08:26:55 by pmessett          #+#    #+#             */
/*   Updated: 2023/06/19 22:49:36 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_tail(t_list **list, t_list *new_node)
{
	t_list	*tail;

	tail = find_tail(*list);
	if (!*list)
		*list = new_node;
	else
	{
		tail->next = new_node;
		new_node->prev = tail;
	}
}
