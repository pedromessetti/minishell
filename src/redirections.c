/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:41:44 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/12 13:42:32 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bind_stdin(t_cmd_tb *curr)
{
	if (curr->io.in != -1 && curr->io.in != STDIN_FILENO)
	{
		close(curr->pipe_fd[0]);
		return ;
	}
	if (curr->prev)
		curr->io.in = curr->prev->pipe_fd[0];
	close(curr->pipe_fd[0]);
}

void	bind_stdout(t_cmd_tb *curr)
{
	if (curr->io.out != -1 && curr->io.out != STDOUT_FILENO)
	{
		close(curr->pipe_fd[1]);
		return ;
	}
	if (curr->next)
		curr->io.out = curr->pipe_fd[1];
	else
		close(curr->pipe_fd[1]);
}
