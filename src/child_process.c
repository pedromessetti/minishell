/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:48:32 by pmessett          #+#    #+#             */
/*   Updated: 2023/10/15 12:44:07 by annamarianu      ###   ########.fr       */
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

static int	init_exit_status(int status)
{
	int	return_code;
	int	signal_number;

	return_code = 0;
	signal_number = 0;
	if (WIFEXITED(status))
		return_code = WEXITSTATUS(status);
	else
	{
		return_code = 128;
		if (WIFSIGNALED(status))
			signal_number = WTERMSIG(status);
		else
		{
			if (WIFSTOPPED(status))
				signal_number = SIGSTOP;
			if (WIFCONTINUED(status))
				signal_number = SIGCONT;
		}			
	}
	return (return_code + signal_number);
}

static int	init_stat_loc_after_wait(pid_t last_fork_pid, size_t num_process)
{
	size_t	i;
	int		wait_pid;
	int		stat_loc;
	int		this_stat_loc;
	int		is_stat_sig_int;

	i = 0;
	is_stat_sig_int = 0;
	while (i < num_process)
	{
		wait_pid = wait(&stat_loc);
		if (wait_pid != -1)
			i++;
		if (init_exit_status(stat_loc) == 130 || \
									init_exit_status(stat_loc) == 131)
			is_stat_sig_int = 1;
		if (wait_pid == last_fork_pid)
			this_stat_loc = stat_loc;
	}
	if (is_stat_sig_int)
		ft_putstr_fd("\n", 1);
	return (this_stat_loc);
}

int	wait_all_child(pid_t last_fork_pid, size_t num_proc)
{
	int	stat_loc;

	stat_loc = init_stat_loc_after_wait(last_fork_pid, num_proc);
	return init_exit_status(stat_loc);
}

int	start_process(t_cmd_tb *cmd_tb, t_env **env)
{
	t_cmd_tb	*curr;
	t_cmd_tb	info_cmd = {0};
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
			bind_redirs(curr);
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
	//curr = cmd_tb;
	// exit_status = ft_wait(curr);
	exit_status = wait_all_child(info_cmd.pid, info_cmd.num_process);
	set_exit_code(exit_status, true);
	return exit_status;
}

