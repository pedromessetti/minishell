/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:09 by pmessett          #+#    #+#             */
/*   Updated: 2023/10/15 13:20:40 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Iterates into the env_list and returns the last node*/
t_env	*find_env_tail(t_env *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}

/*Add a new node at the end of the cost env_list*/
void	add_env_tail(t_env **list_head, t_env *new_path)
{
	t_env	*last;

	last = find_env_tail(*list_head);
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

/*Add a new node at the beginning of the env_list*/
t_env	*add_env_node(char *envp)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(envp);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/*Checks if the env_list is empity, if it is, add a new path to the top,
else add a new path in the end*/
t_env	*create_env(t_env *env_list, char *envp)
{
	t_env	*new_list;

	new_list = NULL;
	if (!env_list)
		env_list = add_env_node(envp);
	else
	{
		new_list = add_env_node(envp);
		add_env_tail(&env_list, new_list);
	}
	return (env_list);
}

/*Free the allocated memory for the env_list*/
void	free_env(t_env **env_list)
{
	t_env	*tmp;

	tmp = NULL;
	if (!*env_list)
	{
		set_exit_code(0, true);
		return;
	}
	while (*env_list)
	{
		tmp = (*env_list)->next;
		free((*env_list)->content);
		free(*env_list);
		*env_list = tmp;
	}
}
