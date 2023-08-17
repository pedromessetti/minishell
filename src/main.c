/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/07/15 07:08:26 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_variable(char *buf)
{
	if (ft_strnstr(buf, "$", ft_strlen(buf)))
		return (1);
	return (0);
}

int	valid_variable(char *buf, char **envp)
{
	char	*var;

	if (((var = ft_strnstr(buf, "$", ft_strlen(buf)))))
	{
		if (!handle_variable(var, envp))
			return (0);
	}
	return (1);
}

int	calc_len(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			break ;
	}
	return (i);
}

char	*handle_variable(char *var, char **envp)
{
	int	i;

	i = -1;
	++var;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, calc_len(envp[i])) == 0)
			return (ft_strchr(envp[i], '='));
	}
	return (NULL);
}

void	handle_arg(char *buf, char **envp)
{
	char	**args;
	t_cmd	*list;

	list = NULL;
	if (!buf[0] || ft_str_isspace(buf) || (has_variable(buf) && !valid_variable(buf, envp)))
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
			if (ask_for_exit_status(list->p_f))
				exit(g_last_exit_status);
			child_process(list, envp);
		}
		waitpid(list->pid, &g_last_exit_status, 0);
		free_path_list(&list);
	}
}

void	init(char **envp)
{
	char	*input;

	while (1)
	{
		input = readline(WHITE "minishell> " RESET);
		add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		handle_arg(input, envp);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	check_ac(ac);
	init(envp);
	return (0);
}
