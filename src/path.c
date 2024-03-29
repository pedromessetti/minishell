/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:17 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/14 22:10:46 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Set and returns a array of possible paths by iterate into .env file
to find the PATH variable and split the result by the ':'*/
char	**set_possible_paths(t_env **env)
{
	char	*path;
	char	**paths_arr;

	path = ft_getenv("PATH", env);
	if (!path)
	{
		ft_printf("minishell: PATH not set\n");
		return (NULL);
	}
	paths_arr = ft_split(path, ':');
	return (paths_arr);
}

int	check_exit_code(char *s1, char *s2, int flag)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	ft_putendl_fd(str, STDERR_FILENO);
	set_exit_code(flag,true);
	free(str);
	return (flag);
}

/*Find the correct path by tryng to acess all the possible paths*/
t_cmd_tb	*find_path(t_cmd_tb *cmd_tb, char **possible_paths, char *cmd,
		char **args)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (possible_paths[++i])
	{
		tmp = ft_multi_strjoin("/", possible_paths[i], cmd, NULL);
		if (!access(tmp, F_OK))
			break ;
		free(tmp);
		tmp = NULL;
	}
	if (!tmp || (!possible_paths[i]))
		check_exit_code(cmd,": command not found", 127);
	cmd_tb = set_cmd_tb(cmd_tb, tmp, args);
	return (cmd_tb);
}

t_cmd_tb	*choose_handle(char *cmd, t_cmd_tb *cmd_tb, char **args,
		t_env **env)
{
	char	**possible_paths;
	char	*tmp;
	if (ft_isdir(cmd))
	{
		if (access(cmd, F_OK) == -1)
			check_exit_code(cmd ,": No such file or directory",1);
		tmp = ft_strdup(cmd);
		cmd_tb = set_cmd_tb(cmd_tb, tmp, args);
	}
	else if (ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0)
	{
		tmp = ft_strdup(cmd);
		cmd_tb = set_cmd_tb(cmd_tb, tmp, args);
	}
	else
	{
		possible_paths = set_possible_paths(env);
		if (!possible_paths)
			return (NULL);
		cmd_tb = find_path(cmd_tb, possible_paths, cmd, args);
		free_matrix(possible_paths);
	}
	return (cmd_tb);
}
