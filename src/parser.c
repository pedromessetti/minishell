/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:39:11 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/15 00:19:42 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_token *tokens, t_env **env)
{
	t_cmd_tb	*cmd_list;
	t_cmd_tb	*head;
	t_token		*redir_head;
	t_token		**redir_tmp;
	t_token		*curr;

	cmd_list = NULL;
	head = NULL;
	redir_head = NULL;
	while (tokens)
	{
		// TODO: Migrate current `cd` implementation to child_process.c
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
		if (tokens->type == TOKEN_IDENTIFIER)
		{
			exec_identifier(tokens, &head, env, redir_head);
			cmd_list = find_cmd_tb_tail(head);
		}
		if (ft_strcmp(tokens->content, "|") == 0)
		{
			if (!tokens->next && !cmd_list)
			{
				ft_printf("minishell: syntax error near unexpected token `|'\n");
				if (tokens->prev)
				{
					free_cmd_tb(&cmd_list);
					free_tokens(&tokens);
				}
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
			curr = duplicate_token(tokens->next);
			add_token_to_tail(redir_tmp, curr);
		}
		tokens = tokens->next;
	}
	// print_list(head);
	start_process(head, env);
	free_cmd_tb(&head);
}
