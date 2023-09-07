/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/09/08 00:41:35 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char **envp)
{
	char	*prompt;

	create_env(envp);
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		if (ft_strnstr(prompt, "exit", ft_strlen(prompt)))
		{
			prompt = ft_strnstr(prompt, "exit", ft_strlen(prompt));
			prompt += 4;
			while (*prompt == ' ')
				prompt++;
			check_exit_status(prompt);
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		lex(prompt);
		free(prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	check_ac(ac);
	init(envp);
	return (0);
}
