/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:33 by pmessett          #+#    #+#             */
/*   Updated: 2023/10/15 13:00:24 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(const char *directory, t_env **env)
{
	int exit_code;
	
	if (ft_strncmp(directory, "~/", 2) == 0 || ft_strcmp(directory, "~") == 0
		|| !*directory)
	{
		chdir(ft_getenv("HOME", env));
	}
	else
	{
		if (chdir(directory) != 0)
		{
			perror("minishell: cd");
			exit_code = 1;
		}
		else
			exit_code = 0;
	}
	char *cdir = getcwd(NULL,0);
	char *tmp = ft_strjoin("PWD=", cdir);
	set_env(tmp, env);
	free(tmp);
	free(cdir);
	set_exit_code(exit_code, true);
}

void	exec_pwd(int fd)
{
	char	*cdir;

	cdir = getcwd(NULL, 0);
	if (!cdir)
		set_exit_code(1, true);
	ft_putendl_fd(cdir, fd);
	free(cdir);
	set_exit_code(0, true);
}

void	exec_echo(char *arg, int fd, t_env **env)
{
	(void)env;
	if (arg)
		ft_putendl_fd(arg, fd);
	else if (!arg)
		ft_putendl_fd("", fd);
	set_exit_code(0, true);
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

void	exec_identifier(t_token *token, t_cmd_tb **cmd_list, t_env **env,
		t_token *redirs)
{
	char		**args;
	int			args_count;
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
	if (!*cmd_list)
	{
		free_matrix(args);
		return ;
	}
	tmp = find_cmd_tb_tail(*cmd_list);
	tmp->redirs = redirs;
	// cmd_io = &tmp->io;
	// *cmd_io = *io;
	// io->in = -1;
	// io->out = -1;
	// if (cmd_io->in == -1)
	// 	cmd_io->in = STDIN_FILENO;
	// if (cmd_io->out == -1)
	// 	cmd_io->out = STDOUT_FILENO;
}


// int	ft_exit(t_cmd_tb **cmd)
// {
// 	int	n;

// 	n = set_exit_code(0, false);
// 	if (!(*cmd)->args[1] && free(cmd))
// 		exit (set_exit_code(0, false));
// 	else
// 	{
// 		if ((*cmd)->args[2] && !check_exit_arg((*cmd)->args[1]))
// 		{
// 			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
// 			free(0, data, cmd, 1);
// 			return (set_exit_code(1, true));
// 		}
// 		if (check_exit_arg((*cmd)->args[1]) && free(cmd))
// 			return (set_exit_code(2, true));
// 		n = check_number((*cmd)->args[1]);
// 	}
// 	free(cmd);
// 	exit (set_exit_code(n, true));
// }