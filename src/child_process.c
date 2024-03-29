/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:48:32 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/15 00:25:54 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	exec_cmd(t_cmd_tb *cmd_list, t_env **env)
{
	char	**tmp;

	tmp = get_full_env(env);
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
		if (ft_strcmp(cmd_list->cmd_path, "echo") == 0)
			exec_echo(cmd_list->args[0], STDOUT_FILENO, env);
		else if (ft_strcmp(cmd_list->cmd_path, "cd") == 0)
			exec_cd(cmd_list->args[0], env);
		else if (ft_strcmp(cmd_list->cmd_path, "pwd") == 0)
			exec_pwd(STDOUT_FILENO);
		else if (ft_strcmp(cmd_list->cmd_path, "env") == 0)
			print_env(env, cmd_list->dup2_fd[1]);
		else
			execve(cmd_list->cmd_path, cmd_list->args, tmp);
		free_matrix(tmp);
		close(cmd_list->dup2_fd[0]);
		close(cmd_list->dup2_fd[1]);
		free_cmd_tb(&cmd_list);
		set_exit_code(errno, true);
	}
	free_cmd_tb(&cmd_list);
	exit(set_exit_code(-1, false));
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

static int	init_stat_loc_after_wait(t_cmd_tb *curr)
{
	int		stat_loc;
	int		is_stat_sig_int;

	is_stat_sig_int = 0;
	stat_loc = 0;
	while (curr)
	{
		waitpid(curr->pid, &stat_loc, 0);
		if (init_exit_status(stat_loc) == 130 || \
			init_exit_status(stat_loc) == 131)
			is_stat_sig_int = 1;
		curr = curr->next;
	}
	if (is_stat_sig_int)
		ft_putstr_fd("\n", 1);
	return (stat_loc);
}

int	wait_all_child(t_cmd_tb *curr)
{
	int	stat_loc;

	stat_loc = init_stat_loc_after_wait(curr);
	return init_exit_status(stat_loc);
}

int	start_process(t_cmd_tb *cmd_tb, t_env **env)
{
	t_cmd_tb	*curr;
	int			exit_status;

	curr = cmd_tb;
	if (!curr)
		return (0);
	while (curr)
	{
		if (curr->cmd_path && ft_strcmp(curr->cmd_path, "unset") == 0 && !curr->next && !curr->prev)
			unset_env(curr->args[1], env); // TODO: Add suport to multiple args
		else if (curr->cmd_path && ft_strcmp(curr->cmd_path, "export") == 0 && !curr->next && !curr->prev)
			set_env(curr->args[1], env); // TODO: Add suport to multiple args
		else
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
		}
		curr = curr->next;
	}
	close_all_pipes(cmd_tb);
	curr = cmd_tb;
	exit_status = wait_all_child(curr);
	set_exit_code(exit_status, true);
	return(exit_status);
}
