/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:52 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/12 13:49:53 by pmessett         ###   ########.fr       */
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
	int		i;

	env = NULL;
	(void)av;
	check_ac(ac);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	while (envp[++i])
		env = create_env(env, envp[i]);
	init(&env);
	free_env(&env);
	return (0);
}
