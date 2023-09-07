/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_tail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:20:29 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:20:31 by pedro            ###   ########.fr       */
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
