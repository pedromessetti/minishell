/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:15:47 by pedro             #+#    #+#             */
/*   Updated: 2023/09/08 00:14:00 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Set and returns a array of possible paths by iterate into .env file
to find the PATH variable and split the result by the ':'*/
char	**set_possible_paths(void)
{
	char	*path;
	char	**paths_arr;

	path = ft_getenv("PATH");
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
		if (possible_paths[i + 1])
			free(tmp);
	}
	if (!tmp || (!possible_paths[i]))
	{
		ft_printf("minishell: %s: command not found\n", cmd);
		free(tmp);
		return (NULL);
	}
	cmd_tb = set_cmd_tb(cmd_tb, tmp, args);
	return (cmd_tb);
}

t_cmd_tb	*choose_handle(char *cmd, t_cmd_tb *cmd_list, char **args)
{
	char	**possible_paths;

	if (ft_isdir(cmd))
	{
		if (access(cmd, F_OK) == -1)
			ft_printf("minishell: %s: No such file or directory\n", cmd);
		cmd_list = set_cmd_tb(cmd_list, cmd, args);
	}
	else
	{
		possible_paths = set_possible_paths();
		cmd_list = find_path(cmd_list, possible_paths, cmd, args);
		free_matrix(possible_paths);
	}
	return (cmd_list);
}
