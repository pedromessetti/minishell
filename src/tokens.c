/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:48:24 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/12 20:34:47 by pmessett         ###   ########.fr       */
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
void	add_token_to_tail(t_token **head, t_token *new_node)
{
	t_token	*last;

	if (!new_node)
		return ;
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
		add_token_to_tail(&tokens, tmp);
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

t_token*	duplicate_token(t_token *token)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(token->content);
	new_token->type = token->type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}