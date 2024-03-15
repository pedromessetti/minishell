/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:48:55 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/14 23:38:26 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ident_type(char *str, int len)
{
	if (ft_strchr("|<>", str[0]))
		return (TOKEN_OPERATOR);
	if (ft_isalnum(str[0]) || ft_isdir(str) || is_keyword(str, len))
		return (TOKEN_IDENTIFIER);
	if (str[0] == '$')
		return (TOKEN_VARIABLE);
	if (str[0] == '-')
		return (TOKEN_ARG);
	return (-1);
}

void	handle_literal(t_token **token, char *prompt, int *i)
{
	int	start;
	int	end;

	start = *i;
	(*i)++;
	while (prompt[*i] && prompt[*i] != prompt[start])
		(*i)++;
	end = *i;
	*token = set_token(*token, TOKEN_LITERAL, prompt + start + 1, end - 1
			- start);
	(*i)++;
}

void	lex(char *prompt, t_env **env)
{
	int		i;
	int		start;
	int		end;
	int		type;
	t_token	*token;

	i = 0;
	token = NULL;
	while (prompt[i])
	{
		if (ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			handle_literal(&token, prompt, &i);
			continue ;
		}
		start = i;
		end = start;
		while (prompt[end] && !ft_isspace(prompt[end]))
			end++;
		type = ident_type(prompt + start, end - start);
		token = set_token(token, type, prompt + start, end - start);
		i = end;
	}
	iter_tokens(&token);
	// print_token_list(token);
	parser(token, env);
	free_tokens(&token);
}
