/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:33 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/14 23:59:16 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(const char *directory, t_env **env)
{
	if (ft_strncmp(directory, "~/", 2) == 0 || ft_strcmp(directory, "~") == 0
		|| !*directory)
	{
		if (chdir(ft_getenv("HOME", env))!=0)
			perror("minishell: cd");
	}
	else
	{
		if (chdir(directory) != 0)
			perror("minishell: cd");
	}
	char *cdir = getcwd(NULL,0);
	char *old_tmp = ft_strjoin("OLDPWD=", ft_getenv("PWD", env));
	set_env(old_tmp, env);
	char *tmp = ft_strjoin("PWD=", cdir);
	set_env(tmp, env);
	free(tmp);
	free(old_tmp);
	free(cdir);
}

void	exec_pwd(int fd)
{
	char	*cdir;

	cdir = getcwd(NULL, 0);
	ft_putendl_fd(cdir, fd);
	free(cdir);
}

void	exec_echo(char *arg, int fd, t_env **env)
{
	if (arg && arg[0] == '$')
	{
		if (ft_getenv(arg, env))
			ft_putendl_fd(ft_getenv(arg, env), fd);
		else
			ft_putendl_fd("", fd);
	}
	else if (arg)
		ft_putendl_fd(arg, fd);
	else if (!arg)
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
}
