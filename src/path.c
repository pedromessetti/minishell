/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:15:47 by pedro             #+#    #+#             */
/*   Updated: 2023/08/30 16:15:00 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Set and returns a array of possible paths by iterate into envp untill
find the PATH variable and split the result by the ':'*/
char	**set_possible_paths(char **envp)
{
	char	*path;
	char	**paths_arr;
	int		i;

	path = NULL;
	paths_arr = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!(ft_strncmp(envp[i], "PATH=", 5)))
		{
			path = envp[i];
			break ;
		}
	}
	path = ft_substr(path, 5, ft_strlen(path));
	paths_arr = ft_split(path, ':');
	free(path);
	return (paths_arr);
}

/*Find the correct path by tryng to acess all the possible paths*/
t_cmd_tb	*find_path(t_cmd_tb *path_list, char **possible_paths, char *cmd, char **args)
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
		if (possible_paths[i + 1])
			free(tmp);
	}
	if (!tmp || (!possible_paths[i]))
		ft_printf(RED "minishell: %s: command not found\n" RESET,	cmd);
	cmd = tmp;
	path_list = set_cmd_tb_list(path_list, cmd, args);
	return (path_list);
}

t_cmd_tb	*handle_str_error(char *buf, t_cmd_tb *path_list)
{
	ft_printf(RED "minishell: %s: command not found\n" RESET, buf);
	path_list = set_cmd_tb_list(path_list, NULL, NULL);
	return (path_list);
}

t_cmd_tb	*choose_handle(char *cmd, char **envp, t_cmd_tb *cmd_list, char **args)
{
	char	**possible_paths;

	// Absolute path
	if (ft_isdir(cmd))
	{
		if (access(cmd, F_OK) == -1)
			ft_printf(RED "minishell: %s: No such file or directory\n" RESET, cmd);
		cmd_list = set_cmd_tb_list(cmd_list, cmd, args);
	}
	else
	{
		possible_paths = set_possible_paths(envp);
		cmd_list = find_path(cmd_list, possible_paths, cmd, args);
		free_matrix(possible_paths);
	}
	return (cmd_list);
}
