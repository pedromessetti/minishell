/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/09/12 13:46:23 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *tokens, t_env **env)
{
	t_cmd_tb	*cmd_list;
	t_io		io;
	t_io		*cmd_io;

	cmd_list = NULL;
	io.in = -1;
	io.out = -1;
	while (tokens)
	{
		if (ft_strcmp(tokens->content, "cd") == 0)
		{
			tokens = tokens->next;
			if ((tokens && ft_strcmp(tokens->content, "|") == 0)
				|| (tokens->next && ft_strcmp(tokens->next->content, "|") == 0))
			{
				tokens = tokens->next;
				continue ;
			}
			else if (tokens && tokens->type == TOKEN_ARG && tokens->next
				&& tokens->next->type == TOKEN_ARG)
			{
				ft_printf("minishell: cd: too many arguments\n");
				while (tokens && tokens->type == TOKEN_ARG)
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
			exec_pwd(STDOUT_FILENO);
		else if (ft_strcmp(tokens->content, "env") == 0)
			print_env(env, STDOUT_FILENO);
		else if (ft_strcmp(tokens->content, "echo") == 0)
		{
			if (!tokens->next)
				exec_echo(NULL, STDOUT_FILENO, env);
			while (tokens->next && tokens->next->type == TOKEN_ARG)
			{
				// TODO: Join all the arguments before sending to exec_echo
				exec_echo(tokens->next->content, STDOUT_FILENO, env);
				tokens = tokens->next;
			}
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
			exec_identifier(tokens, &cmd_list, env, &io);
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
			cmd_io = &io;
			if (cmd_list)
				cmd_io = &cmd_list->io;
			if (!tokens->next)
			{
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
				free_cmd_tb(&cmd_list);
				return (-1);
			}
			else if (ft_strcmp(tokens->content, ">") == 0)
			{
				cmd_io->out = open(tokens->next->content,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd_io->out == -1)
					ft_printf("minishell: %s: %s\n", tokens->next->content,
						strerror(errno));
			}
			else if (ft_strcmp(tokens->content, ">>") == 0)
			{
				cmd_io->out = open(tokens->next->content,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmd_io->out == -1)
					ft_printf("minishell: %s: %s\n", tokens->next->content,
						strerror(errno));
			}
			else if (ft_strcmp(tokens->content, "<") == 0)
			{
				cmd_io->in = open(tokens->next->content, O_RDONLY);
				if (cmd_io->in == -1)
					ft_printf("minishell: %s: %s\n", tokens->next->content,
						strerror(errno));
			}
		}
		tokens = tokens->next;
	}
	start_process(cmd_list, env);
	free_cmd_tb(&cmd_list);
	return (0);
}
