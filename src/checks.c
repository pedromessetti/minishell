/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:43:36 by pmessett          #+#    #+#             */
/*   Updated: 2023/06/30 08:29:24 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ac(int ac)
{
	if (ac == 1)
		return ;
	else
		exit(EXIT_FAILURE);
}

// int	*check_fd(int fd[], char **av, int ac)
// {
// 	int	flags;

// 	flags = O_CREAT | O_WRONLY | O_TRUNC;
// 	if (is_here_doc(av[1]))
// 		flags = O_CREAT | O_WRONLY | O_APPEND;
// 	fd[1] = open(av[ac - 1], flags, 0644);
// 	if (fd[1] == -1)
// 	{
// 		ft_printf("minishell: Error opening/creating the file\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (!is_here_doc(av[1]))
// 	{
// 		fd[0] = open(av[1], O_RDONLY);
// 		if (fd[0] == -1)
// 		{
// 			perror(av[1]);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (fd);
// }

// int	check_builtin(char *av)
// {
// 	if (ft_strncmp(av, "exit\0", ft_strlen("exit") + 1) == 0 || ft_strncmp(av,
// 			"exit ", ft_strlen("exit ")) == 0)
// 		return (1);
// 	if (ft_strncmp(av, "cd\0", ft_strlen("cd") + 1) == 0 || ft_strncmp(av,
// 			"cd ", ft_strlen("cd ")) == 0)
// 		return (1);
// 	return (0);
// }

void	check_exit_status(char *arg)
{
	if (ft_str_is_num(arg))
		return ;
	else
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
}

// void	check_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) == 0)
// 			return ;
// 		i++;
// 	}
// 	ft_printf("minishell: PATH not set\n");
// 	exit(EXIT_FAILURE);
// }

// int	ask_for_exit_status(char **args)
// {
// 	if (ft_strcmp(args[0], "/usr/bin/echo") == 0
// 		&& (ft_strcmp(args[1], "$?") == 0))
// 	{
// 		ft_putnbr_fd(g_last_exit_status, STDOUT_FILENO);
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		return (1);
// 	}
// 	return (0);
// }
