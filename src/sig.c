/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:45:56 by pedro             #+#    #+#             */
/*   Updated: 2023/09/09 17:46:15 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			set_exit_code(130, true);
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
	if (sig == SIGQUIT)
		write(1, "\n", 1);
}

int	set_exit_code(int i, bool flag)
{
	static int	code;

	if (flag)
		code = i;
	return (code);
}