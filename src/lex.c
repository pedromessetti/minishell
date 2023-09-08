/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:45:09 by pedro             #+#    #+#             */
/*   Updated: 2023/09/08 00:55:07 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ident_type(char *str, int len)
{
	// Check if the string is an argument (if flag is set)
	// if (*next_token_type == TOKEN_ARG) {
	// 		*next_token_type = -1; // Reset the flag
	// 		return (TOKEN_ARG);
	// }
	// // Check if the string is a file (if flag is set)
	// if (*next_token_type == TOKEN_FILE) {
	// 		*next_token_type = -1;
	// 		return (TOKEN_FILE);
	// }
	if (is_literal_string(str, len))
		return (TOKEN_LITERAL);
	if (is_keyword(str, len))
		return (TOKEN_KEYWORD);
	if ((ft_isalnum(str[0]) || ft_isdir(str)))
		return (TOKEN_IDENTIFIER);
	if (len == 1 && ft_strchr("|<>", str[0]))
		return (TOKEN_OPERATOR);
	if (str[0] == '$')
		return (TOKEN_ENV_VARIABLE);
	if (str[0] == '-')
		return (TOKEN_ARG);
	return (-1);
}

void	lex(char *prompt)
{
	int i;
	int start;
	int end;
	int type;
	t_token *token = NULL;

	i = 0;
	while (prompt[i])
	{
		if (ft_isspace(prompt[i]))
			i++;
		start = i;
		end = start;
		while (prompt[end] && !ft_isspace(prompt[end]))
			end++;
		type = ident_type(prompt + start, end - start);
		token = set_token(token, type, prompt + start, end - start);

		// if (echo_flag && type != TOKEN_OPERATOR && type != TOKEN_KEYWORD)
		// 	type = TOKEN_LITERAL; // Treat as literal string
		// else if (type == TOKEN_OPERATOR)
		// 	echo_flag = 0; // Reset flag after finding operator
		// if (type == TOKEN_IDENTIFIER && ft_strncmp(prompt + start, "grep",4) == 0)
		// 	next_token_type = TOKEN_ARG;
		// if (type == TOKEN_OPERATOR && is_redirection(prompt + start, end- start))
		// 	next_token_type = TOKEN_FILE;
		i = end;
	}
	// merge_literal(token);
	// print_token_list(token);
	parser(token);
	free_tokens(&token);
}

// TODO: remove from token list does who have type == -1