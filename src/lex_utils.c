/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:48:00 by pedro             #+#    #+#             */
/*   Updated: 2023/09/10 22:55:17 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_literal_string(char *str, int len)
{
	if (len < 2)
		return (0);
	if ((str[0] == '"' || str[len - 1] == '"') || (str[0] == '\'' || str[len
			- 1] == '\''))
		return (1);
	return (0);
}

int	is_keyword(char *str, int len)
{
	if (len == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (1);
	if (len == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (1);
	if (len == 6 && ft_strncmp(str, "export", 6) == 0)
		return (1);
	if (len == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (1);
	if (len == 4 && ft_strncmp(str, "echo", 4) == 0)
		return (1);
	if (len == 3 && ft_strncmp(str, "env", 3) == 0)
		return (1);
	if (len == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	return (0);
}

void	iter_tokens(t_token **tokens)
{
	t_token *token = *tokens;
	while (token)
	{
		if ((!token->prev || token->prev->type == TOKEN_OPERATOR)
			&& token->type == TOKEN_ARG)
			token->type = TOKEN_IDENTIFIER;
		if (token->prev && token->prev->type == TOKEN_IDENTIFIER
			&& token->type == TOKEN_IDENTIFIER)
		{
			token->type = TOKEN_ARG;
			while (token->next && token->next->type != TOKEN_OPERATOR)
			{
				token->next->type = TOKEN_ARG;
				token = token->next;
			}
		}
		if (ft_strncmp(token->content, "grep", 4) == 0)
			token->next->type = TOKEN_ARG;
		if (ft_strncmp(token->content, "echo", 4) == 0)
		{
			while (token->next && token->next->type != TOKEN_OPERATOR)
			{
				token->next->type = TOKEN_ARG;
				token = token->next;
			}
		}
		if (ft_strncmp(token->content, "export", 6) == 0
			|| ft_strncmp(token->content, "unset", 5) == 0)
		{
			while (token->next && token->next->type != TOKEN_OPERATOR)
			{
				token->next->type = TOKEN_ARG;
				token = token->next;
			}
		}
		if ((!token->prev || token->prev->type == TOKEN_OPERATOR)
			&& token->type == TOKEN_LITERAL)
			token->type = TOKEN_IDENTIFIER;
		if (is_redirection(token->content) && token->next)
			token->next->type = TOKEN_FILE;
		token = token->next;
	}
}