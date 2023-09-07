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

void	check_exit_status(char *arg)
{
	if (ft_str_is_num(arg))
		return ;
	else
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
}

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
