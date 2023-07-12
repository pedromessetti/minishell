/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/07/12 08:12:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_variable(char *var, char **envp)
{
	int	i;

	i = -1;
	var = ft_strip(++var);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			var = ft_strchr(envp[i], '=');
			break ;
		}
		var = NULL;
	}
	return (++var);
}

void	handle_arg(char *buf, char **envp)
{
	char	**args;
	t_cmd	*list;

	list = NULL;
	if (!buf[0] || ft_str_isspace(buf))
		return ;
	if (haspipe(buf))
	{
		args = ft_split(buf, '|');
		list = define_multiple_path(list, args, envp);
		start_process(list, envp);
		free_matrix(args);
		free_path_list(&list);
	}
	else
	{
		list = define_path(list, buf, envp);
		list->pid = fork();
		if (list->pid == 0)
		{
			if (ask_for_exit_status(list->path_and_cmd))
				exit(g_last_exit_status);
			child_process(list, envp);
		}
		waitpid(list->pid, &g_last_exit_status, 0);
		free_path_list(&list);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)av;
	check_ac(ac);
	while (1)
	{
		input = readline(WHITE "minishell> " RESET);
		add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		else
		{
			handle_arg(input, envp);
			free(input);
		}
	}
	free(input);
	return (0);
}
