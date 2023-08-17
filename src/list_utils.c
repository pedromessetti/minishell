/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:43:27 by pmessett          #+#    #+#             */
/*   Updated: 2023/06/30 08:29:24 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if the path_list is empity, if it is, add a new path to the top,
else add a new path in the end*/
t_cmd	*set_cmd_list(t_cmd *path_list, char *path, char **p_f)
{
	t_cmd	*new_list;

	new_list = NULL;
	if (!path_list)
		path_list = add_path(path, p_f);
	else
	{
		new_list = add_path(path, p_f);
		add_tail(&path_list, new_list);
	}
	return (path_list);
}

/*Free the allocated memory for the paths_list*/
void	free_path_list(t_cmd **path_list)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!*path_list)
		return ;
	while ((*path_list)->prev)
		*path_list = (*path_list)->prev;
	while (*path_list)
	{
		tmp = (*path_list)->next;
		if ((*path_list)->p_f)
			free_matrix((*path_list)->p_f);
		if (!(*path_list)->path)
			free((*path_list)->path);
		free(*path_list);
		*path_list = tmp;
	}
}

/*Add a new node at the beginning of the paths_list*/
t_cmd	*add_path(char *path, char **p_f)
{
	t_cmd	*new_path;

	new_path = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_path)
		return (NULL);
	new_path->path = path;
	new_path->p_f = p_f;
	new_path->next = NULL;
	new_path->prev = NULL;
	return (new_path);
}

/*Add a new node at the end of the cost paths_list*/
void	add_tail(t_cmd **list_head, t_cmd *new_path)
{
	t_cmd	*last;

	last = find_last(*list_head);
	if (!list_head)
		return ;
	if (!*list_head)
		*list_head = new_path;
	else
	{
		last->next = new_path;
		new_path->prev = last;
	}
}

/*Iterates into the paths_list and returns the last node*/
t_cmd	*find_last(t_cmd *paths_list)
{
	if (!paths_list)
		return (NULL);
	while (paths_list->next)
		paths_list = paths_list->next;
	return (paths_list);
}
