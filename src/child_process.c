/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:48:32 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/06 09:57:00 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		g_last_exit_status = 0;

void	exec_cmd(t_cmd_tb *cmd_list, char **envp)
{
	if (cmd_list->path)
		execve(cmd_list->path, cmd_list->args, envp);
	close(cmd_list->dup2_fd[0]);
	close(cmd_list->dup2_fd[1]);
	free_path_list(&cmd_list);
	exit(EXIT_FAILURE);
}

void	bind_stdin(t_cmd_tb *curr)
{
	if (curr->prev)
	{
		printf("Redirecionando stdin do comando %s para o pipe de leitura do comando anterior\n", curr->args[0]);
		curr->dup2_fd[0] = dup2(curr->prev->pipe_fd[0], STDIN_FILENO);
	}
	else
		curr->dup2_fd[0] = dup2(curr->pipe_fd[0], STDIN_FILENO);
	close(curr->pipe_fd[0]);
}

void	bind_stdout(t_cmd_tb *curr)
{
	if (curr->next)
	{
		printf("Redirecionando stdout do comando %s para o pipe de escrita do próximo comando\n", curr->args[0]);
		curr->dup2_fd[1] = dup2(curr->pipe_fd[1], STDOUT_FILENO);
	}
	else
		curr->dup2_fd[1] = dup2(curr->dup2_fd[1], STDOUT_FILENO);
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
	// g_last_exit_status = exit_status;
	return (exit_status);
}

int	start_process(t_cmd_tb *path_list, char **envp)
{
	t_cmd_tb *curr;
	

	curr = path_list;

	while (curr)
	{
		if (pipe(curr->pipe_fd) == -1)
		{
			return (1);
			perror("Erro ao criar pipe");
		}
		curr->pid = fork();
		if (curr->pid == 0)
		{
			printf("Processo filho %d executando comando: %s\n", getpid(), curr->args[0]);
			if (curr != path_list)
				bind_stdin(curr);
			if (curr->next)
				bind_stdout(curr);
			exec_cmd(curr, envp);
		}
		if (curr != path_list)
			close(curr->prev->pipe_fd[0]);
		close(curr->pipe_fd[1]);
		curr = curr->next;
	}
	close_all_pipes(path_list);
	curr = path_list;
	int exit_status = ft_wait(curr);
	// free_path_list(&path_list);
	return (exit_status);
}