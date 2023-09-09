/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 07:36:23 by pedro             #+#    #+#             */
/*   Updated: 2023/09/06 16:54:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if the path_list is empity, if it is, add a new path to the top,
else add a new path in the end*/
t_token	*set_token_list(t_token *token_lst, int type, char *str, int len)
{
	t_token	*tmp;

	tmp = NULL;
	if (!token_lst)
		token_lst = add_token(type, str, len);
	else
	{
		tmp = add_token(type, str, len);
		add_token_tail(&token_lst, tmp);
	}
	return (token_lst);
}

/*Free the allocated memory for the paths_list*/
void	free_token_lst(t_token **token_lst)
{
	t_token	*tmp;

	tmp = NULL;
	if (!*token_lst)
		return ;
	while ((*token_lst)->prev)
		*token_lst = (*token_lst)->prev;
	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		if ((*token_lst)->content)
			free((*token_lst)->content);
		free(*token_lst);
		*token_lst = tmp;
	}
}

/*Add a new node at the beginning of the paths_list*/
t_token	*add_token(int type, char *str, int len)
{
    (void)len;
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
    new_token->content = ft_substr(str, 0, len);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/*Add a new node at the end of the cost paths_list*/
void	add_token_tail(t_token **list_head, t_token *new_token)
{
	t_token	*last;

	last = find_last_token(*list_head);
	if (!list_head)
		return ;
	if (!*list_head)
		*list_head = new_token;
	else
	{
		last->next = new_token;
		new_token->prev = last;
	}
}

/*Iterates into the paths_list and returns the last node*/
t_token	*find_last_token(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	while (token_lst->next)
		token_lst = token_lst->next;
	return (token_lst);
}

/*Prints the tokens [removable]*/
void	print_token_list(t_token *token_lst)
{
    if (!token_lst)
        return ;
    while (token_lst->prev)
        token_lst = token_lst->prev;
    while (token_lst)
    {
        printf("content: %s | type: %d\n", token_lst->content, token_lst->type);
        token_lst = token_lst->next;
    }
}