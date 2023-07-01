/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:49:42 by pedro             #+#    #+#             */
/*   Updated: 2023/07/01 09:17:51 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(char **envp)
{
	char	*buf;
	int		fd;
	t_cmd	*list;

	list = NULL;
	fd = open("history", O_CREAT | O_WRONLY | O_APPEND, 0644);
	while (1)
	{
		ft_printf(WHITE"my shell> "RESET);
		buf = get_next_line(STDIN_FILENO);
		if (buf)
		{
			if (is_limiter("\n", buf))
				break ;
			write(fd, buf, ft_strlen(buf));
			list = define_path(list, ft_strip(buf), envp);
			free(buf);
		}
	}
	close(fd);
	free(buf);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	check_ac(ac);
	init_minishell(envp);
	return (0);
}
