/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:15:47 by pedro             #+#    #+#             */
/*   Updated: 2023/09/11 10:31:11 by pedro            ###   ########.fr       */
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
	{
		ft_printf("minishell: %s: command not found\n", cmd);
		return (NULL);
	}
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
			ft_printf("minishell: %s: No such file or directory\n", cmd);
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
