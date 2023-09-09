/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:41:07 by pedro             #+#    #+#             */
/*   Updated: 2023/09/08 00:46:17 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Iterates into the token list and returns his last node*/
static t_token	*find_last(t_token *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

/*Add a new node at the end of the token list*/
static void	add_tail(t_token **head, t_token *new_node)
{
	t_token	*last;

	last = find_last(*head);
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

/*Add a new node at the beginning of the token list*/
static t_token	*add_node(int type, char *str, int len)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = ft_substr(str, 0, len);
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/*If the token list is empty add the node at the head,
otherwise add the node at the end*/
t_token	*set_token(t_token *tokens, int type, char *str, int len)
{
	t_token	*tmp;

	tmp = NULL;
	if (!tokens)
		tokens = add_node(type, str, len);
	else
	{
		tmp = add_node(type, str, len);
		add_tail(&tokens, tmp);
	}
	return (tokens);
}

/*Free the allocated memory for the token list*/
void	free_tokens(t_token **token_list)
{
	t_token	*tmp;

	tmp = NULL;
	if (!*token_list)
		return ;
	while ((*token_list)->prev)
		*token_list = (*token_list)->prev;
	while (*token_list)
	{
		tmp = (*token_list)->next;
		if ((*token_list)->content)
			free((*token_list)->content);
		free(*token_list);
		*token_list = tmp;
	}
}

/*Prints the tokens [REMOVE BEFORE DELIVERY]*/
void	print_token_list(t_token *token_list)
{
	if (!token_list)
		return ;
	while (token_list->prev)
		token_list = token_list->prev;
	while (token_list)
	{
		printf("content: %s | type: %d\n", token_list->content,
			token_list->type);
		token_list = token_list->next;
	}
}
