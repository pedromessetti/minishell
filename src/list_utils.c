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
t_cmd_tb	*set_cmd_tb_list(t_cmd_tb *path_list, char *path, char **args)
{
	t_cmd_tb	*new_list;

	new_list = NULL;
	if (!path_list)
		path_list = add_path(path, args);
	else
	{
		new_list = add_path(path, args);
		add_tail(&path_list, new_list);
	}
	return (path_list);
}

/*Free the allocated memory for the paths_list*/
void	free_path_list(t_cmd_tb **path_list)
{
	t_cmd_tb	*tmp;

	tmp = NULL;
	if (!*path_list)
		return ;
	while ((*path_list)->prev)
		*path_list = (*path_list)->prev;
	while (*path_list)
	{
		tmp = (*path_list)->next;
		if ((*path_list)->args)
			free_matrix((*path_list)->args);
		if (!(*path_list)->path)
			free((*path_list)->path);
		free(*path_list);
		*path_list = tmp;
	}
}

/*Add a new node at the beginning of the paths_list*/
t_cmd_tb	*add_path(char *path, char **args)
{
	t_cmd_tb	*new_path;

	new_path = (t_cmd_tb *)malloc(sizeof(t_cmd_tb));
	if (!new_path)
		return (NULL);
	new_path->path = path;
	new_path->args = args;
	new_path->next = NULL;
	new_path->prev = NULL;
	return (new_path);
}

/*Add a new node at the end of the cost paths_list*/
void	add_tail(t_cmd_tb **list_head, t_cmd_tb *new_path)
{
	t_cmd_tb	*last;

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
t_cmd_tb	*find_last(t_cmd_tb *paths_list)
{
	if (!paths_list)
		return (NULL);
	while (paths_list->next)
		paths_list = paths_list->next;
	return (paths_list);
}
