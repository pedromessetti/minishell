/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:30:36 by pedro             #+#    #+#             */
/*   Updated: 2023/09/12 18:24:59 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Add a new node at the end of the cmd_tb*/
static void	add_tail(t_cmd_tb **head, t_cmd_tb *new_node)
{
	t_cmd_tb	*last;

	last = find_cmd_tb_tail(*head);
	if (!head)
		return ;
	if (!*head)
		*head = new_node;
	else
	{
		last->next = new_node;
		new_node->prev = last;
	}
}

/*Add a new node at the beginning of the cmd_tb*/
static t_cmd_tb	*add_node(char *cmd_path, char **args)
{
	t_cmd_tb	*new_node;

	new_node = (t_cmd_tb *)malloc(sizeof(t_cmd_tb));
	if (!new_node)
		return (NULL);
	new_node->cmd_path = cmd_path;
	new_node->args = args;
	new_node->redirs = NULL;
	new_node->io.in = -1;
	new_node->io.out = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/*Iterates into the cmd_tb and returns his last node*/
t_cmd_tb	*find_cmd_tb_tail(t_cmd_tb *cmd_tb)
{
	if (!cmd_tb)
		return (NULL);
	while (cmd_tb->next)
		cmd_tb = cmd_tb->next;
	return (cmd_tb);
}

/*If the command table is empty add the node at the head,
otherwise add the node at the end*/
t_cmd_tb	*set_cmd_tb(t_cmd_tb *cmd_tb, char *cmd_path, char **args)
{
	t_cmd_tb	*new_list;

	new_list = NULL;
	if (!cmd_tb)
		cmd_tb = add_node(cmd_path, args);
	else
	{
		new_list = add_node(cmd_path, args);
		add_tail(&cmd_tb, new_list);
	}
	return (cmd_tb);
}

/*Free the allocated memory for the command table*/
void	free_cmd_tb(t_cmd_tb **cmd_tb)
{
	t_cmd_tb	*tmp;

	tmp = NULL;
	if (!*cmd_tb)
		return ;
	while ((*cmd_tb)->prev)
		*cmd_tb = (*cmd_tb)->prev;
	while (*cmd_tb)
	{
		tmp = (*cmd_tb)->next;
		if ((*cmd_tb)->args)
			free_matrix((*cmd_tb)->args);
		if ((*cmd_tb)->cmd_path)
			free((*cmd_tb)->cmd_path);
		if ((*cmd_tb)->redirs)
			free_tokens(&(*cmd_tb)->redirs);
		free(*cmd_tb);
		*cmd_tb = tmp;
	}
}

// Print the command table [REMOVE BEFORE DELIVERY]
void	print_list(t_cmd_tb *list)
{
	t_cmd_tb	*curr;

	curr = list;
	while (curr)
	{
		printf("path = %s\n", curr->cmd_path);
		for (int i = 0; curr->args[i]; i++)
			printf("args[%i] = %s\n", i, curr->args[i]);
		printf("redirections:\n");
		t_token *redirs = curr->redirs;
		for (int i = 0; redirs; i++)
		{
			printf("	redirs[%i] = %s\n", redirs->type, redirs->content);
			redirs = redirs->next;
		}		
		curr = curr->next;
	}
}
