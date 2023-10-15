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

int g_exit_status = 0;

void	ft_exit(char *str) {
	char **matriz = ft_split(str, ' ');

	if (matriz[1]) {
		if (ft_str_is_num(matriz[1]))
			exit(ft_atoi(matriz[1]));
			
		else {
			printf("minishell: exit: %s: numeric argument required\n",matriz[1]);
			set_exit_code(1, true);
		}
	}
	else
		exit(g_exit_status);
}

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
			printf("exit\n");
			ft_exit(prompt);
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
	return (set_exit_code(0, false));
}