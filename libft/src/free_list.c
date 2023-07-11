/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:01:40 by pmessett             #+#    #+#             */
/*   Updated: 2023/06/19 23:17:00 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    free_list(t_list **list)
{
    t_list *tmp;

    tmp = NULL;
    if (!*list)
        return ;
    *list = ft_find_head((*list));
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->content);
        free(*list);
        *list = tmp;
    }
}