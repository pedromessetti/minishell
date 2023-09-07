/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_head.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:18:33 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:18:35 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates backwards into the list
Returns the first node (head)*/
t_list	*ft_find_head(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->prev)
		list = list->prev;
	return (list);
}
