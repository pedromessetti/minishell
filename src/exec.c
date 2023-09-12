/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 00:27:54 by pedro             #+#    #+#             */
/*   Updated: 2023/09/11 19:13:31 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(const char *directory, t_env **env)
{
	if (ft_strncmp(directory, "~/", 2) == 0 || ft_strcmp(directory, "~") == 0
		|| !*directory)
		chdir(ft_getenv("HOME", env));
	else
	{
		if (chdir(directory) != 0)
			perror("minishell: cd");
	}
}

void	exec_pwd(int fd)
{
	char	*cdir;

	cdir = getcwd(NULL, 0);
	ft_putendl_fd(cdir, fd);
	free(cdir);
}

void	exec_echo(char *arg, int fd)
{
	if (arg)
		ft_putendl_fd(arg, fd);
	else
		ft_putendl_fd("", fd);
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

void	exec_identifier(t_token *token, t_cmd_tb **cmd_list, t_env **env, t_io* io)
{
	char		**args;
	int			args_count;
	t_io		*cmd_io;
	t_cmd_tb	*tmp;

	args = NULL;
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
	*cmd_list = choose_handle(args[0], *cmd_list, args, env);
	tmp = find_cmd_tb_tail(*cmd_list);
	if (!*cmd_list)
	{
		free_matrix(args);
		return ;
	}
	cmd_io = &tmp->io;
	*cmd_io = *io;
	io->in = -1;
	io->out = -1;
	if (cmd_io->in == -1)
		cmd_io->in = STDIN_FILENO;
	if (cmd_io->out == -1)
		cmd_io->out = STDOUT_FILENO;
		
}
