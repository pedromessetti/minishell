/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/09/09 21:28:58 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_env **env)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			exit(EXIT_SUCCESS);
		add_history(prompt);
		if (ft_strnstr(prompt, "exit", ft_strlen(prompt)))
		{
			prompt = ft_strnstr(prompt, "exit", ft_strlen(prompt));
			prompt += 4;
			while (*prompt == ' ')
				prompt++;
			check_exit_status(prompt);
			free_env(env);
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		lex(prompt, env);
		free(prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = NULL;
	(void)av;
	check_ac(ac);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	int i = -1;
	while (envp[++i])
		env = create_env(env, envp[i]);
	init(&env);
	free_env(&env);
	return (0);
}
