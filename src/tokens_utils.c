/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:32:29 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/14 22:05:19 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_args_until_operator(t_token **token_ptr, const char *command,
		size_t len)
{
	t_token	*token;

	token = *token_ptr;
	if (ft_strncmp(token->content, command, len) == 0)
	{
		while (token->next && token->next->type != TOKEN_OPERATOR)
		{
			token->next->type = TOKEN_ARG;
			token = token->next;
		}
	}
	*token_ptr = token;
}

void	set_token_type(t_token **token_ptr, int condition, int new_type)
{
	t_token	*token;

	token = *token_ptr;
	if (condition)
		token->type = new_type;
	*token_ptr = token;
}

void	set_args_for_command(t_token **token_ptr, const char *command)
{
	size_t		len;
	size_t		i;
	const char	*commands[5];

	commands[0] = "grep";
	commands[1] = "echo";
	commands[2] = "export";
	commands[3] = "unset";
	commands[4] = "cd";
	len = sizeof(commands) / sizeof(commands[0]);
	i = -1;
	while (++i < len)
	{
		if (ft_strncmp(command, commands[i], ft_strlen(commands[i])) == 0)
		{
			set_args_until_operator(token_ptr, commands[i],
				ft_strlen(commands[i]));
			break ;
		}
	}
}

void	iter_tokens(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		set_token_type(&token, (!token->prev
				|| token->prev->type == TOKEN_OPERATOR)
			&& token->type == TOKEN_ARG, TOKEN_IDENTIFIER);
		set_token_type(&token, token->prev
			&& token->prev->type == TOKEN_IDENTIFIER
			&& token->type == TOKEN_IDENTIFIER, TOKEN_ARG);
		set_args_for_command(&token, token->content);
		set_token_type(&token, (!token->prev
				|| token->prev->type == TOKEN_OPERATOR)
			&& token->type == TOKEN_LITERAL, TOKEN_IDENTIFIER);
		set_token_type(&token, is_redirection(token->content) && token->next,
			TOKEN_FILE);
		token = token->next;
	}
}
