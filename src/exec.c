/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:27:54 by pedro             #+#    #+#             */
/*   Updated: 2023/09/09 13:36:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(const char *directory)
{
	if (ft_strncmp(directory, "~/", 2) == 0)
		chdir(ft_getenv("HOME"));
	else
	{
		if (chdir(directory) != 0)
			perror("minishell: cd");
	}
}

void exec_pwd(void)
{
	char *cdir = getcwd(NULL, 0);
	printf("%s\n", cdir);
	free(cdir);
}

void	exec_echo(char *arg)
{
	if (arg)
		ft_putendl_fd(arg, STDOUT_FILENO);
	else
		ft_putendl_fd("", STDOUT_FILENO);
}

void	exec_env(void)
{
	int		fd;
	char	*line;

	fd = open(".env", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static char	**add_to_args(char **args, char *str)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(str);
	new_args[i + 1] = NULL;
	if (args)
		free(args);
	return (new_args);
}

void	exec_identifier(t_token *token, t_cmd_tb **cmd_list)
{
	char	**args;
	int		args_count;

	args_count = 1;
	while (token && token->type != TOKEN_OPERATOR)
	{
		args = add_to_args(args, token->content);
		args_count++;
		if (token->next)
			token = token->next;
		else
			break ;
	}
	*cmd_list = choose_handle(args[0], *cmd_list, args);
	if (!*cmd_list)
		free_matrix(args);
}
