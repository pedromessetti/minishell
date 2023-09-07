/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/09/06 17:34:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	has_variable(char *buf)
// {
// 	if (ft_strnstr(buf, "$", ft_strlen(buf)))
// 		return (1);
// 	return (0);
// }

// int	valid_variable(char *buf, char **envp)
// {
// 	char	*var;

// 	if (((var = ft_strnstr(buf, "$", ft_strlen(buf)))))
// 	{
// 		if (!handle_variable(var, envp))
// 			return (0);
// 	}
// 	return (1);
// }

// int	calc_len(char *s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i])
// 	{
// 		if (s[i] == '=')
// 			break ;
// 	}
// 	return (i);
// }

// char	*handle_variable(char *var, char **envp)
// {
// 	int	i;

// 	i = -1;
// 	++var;
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp(envp[i], var, calc_len(envp[i])) == 0)
// 			return (ft_strchr(envp[i], '='));
// 	}
// 	return (NULL);
// }

// void is_input(char *input){
// 	char *ocurr = NULL;
// 	if ((ocurr = ft_strnstr(input, "<", ft_strlen(input))))
// 	{
// 		++ocurr;
// 		if (ft_isspace(*ocurr))
// 			++ocurr;
// 		char **tmp = ft_split(ocurr, ' ');
// 		int infile = open(tmp[0], O_RDONLY);
// 		if (infile == -1)
// 		{
// 			ft_printf(RED "minishell: ");
// 			perror(tmp[0]);
// 			ft_printf(RESET);
// 		}
// 		else
// 			printf("file opened\n");
// 		free_matrix(tmp);
// 	}
// }

// void	handle_arg(char *input, char **envp)
// {
// 	char	**args;
// 	t_cmd_tb	*list;

// 	list = NULL;
// 	if (!input[0] || ft_str_isspace(input) || (has_variable(input) && !valid_variable(input, envp)))
// 		return ;
// 	if (has_redirections(input)) {
// 		is_input(input);
// 	}
// 	if (has_pipe(input))
// 	{
// 		args = ft_split(input, '|');
// 		list = define_multiple_path(list, args, envp);
// 		start_process(list, envp);
// 		free_matrix(args);
// 		free_path_list(&list);
// 	}
// 	else
// 	{
// 		list = define_path(list, input, envp);
// 		list->pid = fork();
// 		if (list->pid == 0)
// 		{
// 			if (ask_for_exit_status(list->args))
// 				exit(g_last_exit_status);
// 			child_process(list, envp);
// 		}
// 		waitpid(list->pid, &g_last_exit_status, 0);
// 		free_path_list(&list);
// 	}
// }

#include "minishell.h"

void	init(char **envp)
{
	char	*prompt;

	create_env(envp);
	while (1)
	{
		prompt = readline(WHITE "minishell> " RESET);
		add_history(prompt);
		if (ft_strnstr(prompt, "exit", ft_strlen(prompt)))
		{
			prompt = ft_strnstr(prompt, "exit", ft_strlen(prompt));
			prompt += 4;
			while (*prompt == ' ')
				prompt++;
			check_exit_status(prompt);
			printf("exit\n");
			// free(prompt);
			exit(EXIT_SUCCESS);
		}
		lex(prompt, envp);
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
