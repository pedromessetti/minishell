/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/09/08 00:51:07 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *tokens)
{
	t_cmd_tb	*cmd_list;

	cmd_list = NULL;
	while (tokens)
	{
		if (ft_strcmp(tokens->content, "cd") == 0)
		{
			tokens = tokens->next;
			if (tokens && ft_strcmp(tokens->content, "|") == 0)
			{
				tokens = tokens->next;
				continue ;
			}
			else if (!tokens)
			{
				exec_cd(ft_getenv("HOME"));
				break ;
			}
			else
				exec_cd(tokens->content);
		}
		else if (ft_strncmp(tokens->content, "env", 3) == 0)
		{
			if (tokens->next)
				tokens = tokens->next;
			else
				exec_env();
		}
		// else if (ft_strcmp(tokens->content, "echo") == 0)
		// {
		//     tokens = tokens->next;
		//     const char **echo_args = (const char **)malloc((token_count - i + 1) * sizeof(const char *));
		//     int arg_index = 0;
		//     if (!echo_args)
		//         return (-1);
		//     while (i < token_count)
		//     {
		//         if (tokens[i].type == TOKEN_OPERATOR && strcmp(tokens[i].content, "|") == 0)
		//             break ;
		//         echo_args[arg_index] = tokens[i].content;
		//         arg_index++;
		//         i++;
		//     }
		//     echo_args[arg_index] = NULL;
		//     exec_echo(echo_args);
		//     free(echo_args);
		// }
		else if (tokens->type == TOKEN_IDENTIFIER)
			exec_identifier(tokens, &cmd_list);
		else if (ft_strcmp(tokens->content, "|") == 0)
		{
			if (!tokens->next)
			{
				ft_printf("minishell: syntax error near unexpected token `|'\n");
				free_cmd_tb(&cmd_list);
				return (-1);
			}
			tokens = tokens->next;
			continue ;
		}
		tokens = tokens->next;
	}
	start_process(cmd_list);
	free_cmd_tb(&cmd_list);
	return (0);
}
