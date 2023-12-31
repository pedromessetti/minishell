/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/10/15 12:54:09 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_token *tokens, t_env **env)
{
	t_cmd_tb	*cmd_list;
	t_cmd_tb	*head;
	t_token		*redir_head;
	t_token		**redir_tmp;
	int			cmd_chain;
	t_token		*curr;
	t_token		*dup_token;

	cmd_chain = 0;
	cmd_list = NULL;
	head = NULL;
	redir_head = NULL;
	while (tokens)
	{
		if (ft_strcmp(tokens->content, "cd") == 0)
		{
			tokens = tokens->next;
			if (!tokens)
			{
				exec_cd(ft_getenv("HOME", env), env);
				break ;
			}
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
				set_exit_code(1, true);
				while (tokens && tokens->type == TOKEN_ARG)
					tokens = tokens->next;
				continue ;
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
			curr = tokens;
			while (curr->next && curr->type != TOKEN_OPERATOR)
			{
				if (ft_strcmp(curr->next->content, "|") == 0)
					cmd_chain = 1;
				curr = curr->next;
			}
			while (tokens->next && tokens->next->type == TOKEN_ARG)
			{
				if (cmd_chain == 0)
					unset_env(tokens->next->content, env);
				tokens = tokens->next;
			}
		}
		else if (ft_strcmp(tokens->content, "export") == 0)
		{
			curr = tokens;
			while (curr->next && curr->type != TOKEN_OPERATOR)
			{
				if (ft_strcmp(curr->next->content, "|") == 0)
					cmd_chain = 1;
				curr = curr->next;
			}
			while (tokens->next && tokens->next->type == TOKEN_ARG)
			{
				if (cmd_chain == 0)
					set_env(tokens->next->content, env);
				tokens = tokens->next;
			}
		}
		else if (tokens->type == TOKEN_IDENTIFIER)
		{
			exec_identifier(tokens, &head, env, redir_head);
			cmd_list = find_cmd_tb_tail(head);
		}
		else if (ft_strcmp(tokens->content, "|") == 0)
		{
			if (!tokens->next && !cmd_list)
			{
				ft_printf("minishell: syntax error near unexpected token `|'\n");
				free_cmd_tb(&cmd_list);
				free_tokens(&tokens);
				return ;
			}
			cmd_list = NULL;
			redir_head = NULL;
			tokens = tokens->next;
			continue ;
		}
		else if (is_redirection(tokens->content))
		{
			if (!tokens->next)
			{
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
				free_cmd_tb(&cmd_list);
				return ;
			}
			redir_tmp = &redir_head;
			if (cmd_list)
				redir_tmp = &cmd_list->redirs;
			if (ft_strcmp(tokens->content, ">>") == 0)
				tokens->next->type = PARSER_REDIR_APPEND;
			else if (ft_strcmp(tokens->content, "<<") == 0)
				tokens->next->type = PARSER_REDIR_HERE_DOC;
			else if (ft_strcmp(tokens->content, ">") == 0)
				tokens->next->type = PARSER_REDIR_OUT;
			else if (ft_strcmp(tokens->content, "<") == 0)
				tokens->next->type = PARSER_REDIR_IN;
			dup_token = duplicate_token(tokens->next);
			add_token_to_tail(redir_tmp, dup_token);
		}
		tokens = tokens->next;
	}
	// print_list(head);
	start_process(head, env);
	// if (dup_token)
	// 	free(dup_token->content);
	free_cmd_tb(&head);
}
