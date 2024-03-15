/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:48:32 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/14 23:07:51 by pmessett         ###   ########.fr       */
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

int	start_process(t_cmd_tb *cmd_tb, t_env **env)
{
	t_cmd_tb	*curr;
	int			exit_status;

	curr = cmd_tb;
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
	exit_status = ft_wait(curr);
	return (exit_status);
}
