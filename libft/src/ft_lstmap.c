/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:20:35 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:20:39 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		temp = ft_add_new_node(f(lst->content));
		if (!temp)
			ft_lstclear(&new_lst, del);
		ft_add_tail(&new_lst, temp);
		lst = lst->next;
	}
	return (new_lst);
}
