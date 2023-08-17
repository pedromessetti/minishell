/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:43:32 by pmessett          #+#    #+#             */
/*   Updated: 2023/07/11 08:58:53 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_status = 0;

void	exec_cmd(t_cmd *path_list, char **envp)
{
	if (path_list->path)
		execve(path_list->path, path_list->p_f, envp);
	close(path_list->dup2_fd[0]);
	close(path_list->dup2_fd[1]);
	free_path_list(&path_list);
	exit(EXIT_FAILURE);
}

void	bind_stdin(t_cmd *curr)
{
	if (curr->prev)
		curr->dup2_fd[0] = dup2(curr->prev->pipe_fd[0], STDIN_FILENO);
	else
		curr->dup2_fd[0] = dup2(curr->pipe_fd[0], STDIN_FILENO);
	close(curr->pipe_fd[0]);
}

void	bind_stdout(t_cmd *curr)
{
	if (curr->next)
		curr->dup2_fd[1] = dup2(curr->pipe_fd[1], STDOUT_FILENO);
	else
		curr->dup2_fd[1] = dup2(curr->dup2_fd[1], STDOUT_FILENO);
	close(curr->pipe_fd[1]);
}

void	close_all_pipes(t_cmd *list)
{
	t_cmd	*tmp;

	tmp = list;
	while (tmp)
	{
		close(tmp->pipe_fd[0]);
		close(tmp->pipe_fd[1]);
		tmp = tmp->next;
	}
}

int	ft_wait(t_cmd *curr)
{
	int	exit_status;

	exit_status = 0;
	while (curr)
	{
		waitpid(curr->pid, &exit_status, 0);
		curr = curr->next;
	}
	g_last_exit_status = exit_status;
	return (exit_status);
}

int	start_process(t_cmd *path_list, char **envp)
{
	t_cmd *curr;

	curr = path_list;
	while (curr)
	{
		if (pipe(curr->pipe_fd) == -1)
			return (1);
		curr->pid = fork();
		if (curr->pid == 0)
		{
			if (curr != path_list)
				bind_stdin(curr);
			if (curr->next)
				bind_stdout(curr);
			if (ask_for_exit_status(curr->p_f))
				exit(g_last_exit_status);
			exec_cmd(curr, envp);
		}
		if (curr != path_list)
			close(curr->prev->pipe_fd[0]);
		close(curr->pipe_fd[1]);
		curr = curr->next;
	}
	close_all_pipes(path_list);
	curr = path_list;
	return (ft_wait(curr));
}