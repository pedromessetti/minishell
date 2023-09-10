/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/09/10 22:38:45 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *tokens, t_env **env)
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
				exec_cd(ft_getenv("HOME", env), env);
				break ;
			}
			else
				exec_cd(tokens->content, env);
		}
		else if (ft_strcmp(tokens->content, "pwd") == 0)
			exec_pwd();
		else if (ft_strcmp(tokens->content, "env") == 0)
			print_env(env);
		else if (ft_strcmp(tokens->content, "echo") == 0)
		{
			if (tokens->next && tokens->next->type == TOKEN_ARG)
				exec_echo(tokens->next->content);
			else
				exec_echo(NULL);
		}
		else if (ft_strcmp(tokens->content, "unset") == 0)
		{
			while (tokens->next && tokens->next->type == TOKEN_ARG)
			{
				unset_env(tokens->next->content, env);
				tokens = tokens->next;
			}
		}
		else if (ft_strcmp(tokens->content, "export") == 0)
		{
			while (tokens->next && tokens->next->type == TOKEN_ARG)
			{
				set_env(tokens->next->content, env);
				tokens = tokens->next;
			}
		}
		else if (tokens->type == TOKEN_IDENTIFIER)
			exec_identifier(tokens, &cmd_list, env);
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
		else if (is_redirection(tokens->content))
		{
			if (!tokens->next)
			{
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
				free_cmd_tb(&cmd_list);
				return (-1);
			}
			tokens = tokens->next;
			continue ;
		}
		tokens = tokens->next;
	}
	start_process(cmd_list, env);
	free_cmd_tb(&cmd_list);
	return (0);
}
