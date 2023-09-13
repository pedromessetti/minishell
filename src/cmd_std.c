/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:41:44 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/13 10:45:53 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bind_stdin(t_cmd_tb *curr)
{
	// fprintf(stderr, "[%s] pre curr->io.in: %d\n", curr->args[0], curr->io.in);
	if (curr->io.in != -1 && curr->io.in != STDIN_FILENO)
	{
		close(curr->pipe_fd[0]);
		return ;
	}
	if (curr->prev)
		curr->io.in = curr->prev->pipe_fd[0];
	close(curr->pipe_fd[0]);
	// fprintf(stderr, "[%s] pos curr->io.in: %d\n", curr->args[0], curr->io.in);

}

void	bind_stdout(t_cmd_tb *curr)
{
	// fprintf(stderr, "[%s] pre curr->io.out: %d\n", curr->args[0], curr->io.out);
	if (curr->io.out != -1 && curr->io.out != STDOUT_FILENO)
	{
		close(curr->pipe_fd[1]);
		return ;
	}
	if (curr->next)
		curr->io.out = curr->pipe_fd[1];
	else
		close(curr->pipe_fd[1]);
	// fprintf(stderr, "[%s] pos curr->io.out: %d\n", curr->args[0], curr->io.out);
}

void bind_redirs(t_cmd_tb *cmd)
{
	t_token	*tmp;
	int	ret;
	
	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == PARSER_REDIR_IN)
			ret = bind_redir_in(cmd, tmp);
		else if (tmp->type == PARSER_REDIR_OUT)
			ret = bind_redir_out(cmd, tmp);
		else if (tmp->type == PARSER_REDIR_APPEND)
			ret = bind_redir_append(cmd, tmp);
		else if (tmp->type == PARSER_REDIR_HERE_DOC)
			ret = bind_redir_here_doc(cmd, tmp);
		if (ret) // TODO: CLEANUP CMD
			exit(EXIT_FAILURE);
		tmp = tmp->next;
	}
	if (cmd->io.in == -1)
		cmd->io.in = STDIN_FILENO;
	if (cmd->io.out == -1)
		cmd->io.out = STDOUT_FILENO;
}