/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:48:32 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/12 05:01:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_cmd_tb *cmd_list, t_env **env)
{
	if (cmd_list->cmd_path)
	{
		if (cmd_list->io.in != STDIN_FILENO)
		{
			cmd_list->dup2_fd[0] = dup2(cmd_list->io.in, STDIN_FILENO);
			close(cmd_list->io.in);
		}
		if (cmd_list->io.out != STDOUT_FILENO)
		{
			cmd_list->dup2_fd[1] = dup2(cmd_list->io.out, STDOUT_FILENO);
			close(cmd_list->io.out);
		}
		execve(cmd_list->cmd_path, cmd_list->args, get_full_env(env));
		close(cmd_list->dup2_fd[0]);
		close(cmd_list->dup2_fd[1]);
	}
	free_cmd_tb(&cmd_list);
	exit(EXIT_FAILURE);
}

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

void	close_all_pipes(t_cmd_tb *list)
{
	t_cmd_tb	*tmp;

	tmp = list;
	while (tmp)
	{
		close(tmp->pipe_fd[0]);
		close(tmp->pipe_fd[1]);
		tmp = tmp->next;
	}
}

int	ft_wait(t_cmd_tb *curr)
{
	int	exit_status;

	exit_status = 0;
	while (curr)
	{
		waitpid(curr->pid, &exit_status, 0);
		curr = curr->next;
	}
	return (exit_status);
}

int	start_process(t_cmd_tb *cmd_tb, t_env **env)
{
	t_cmd_tb	*curr;
	int			exit_status;

	curr = cmd_tb;
	while (curr)
	{
		if (pipe(curr->pipe_fd) == -1)
		{
			perror("Error creating pipe");
			return (1);
		}
		curr->pid = fork();
		if (curr->pid == 0)
		{
			bind_stdin(curr);
			bind_stdout(curr);
			exec_cmd(curr, env);
		}
		if (curr != cmd_tb)
			close(curr->prev->pipe_fd[0]);
		close(curr->pipe_fd[1]);
		curr = curr->next;
	}
	close_all_pipes(cmd_tb);
	curr = cmd_tb;
	exit_status = ft_wait(curr);
	return (exit_status);
}
