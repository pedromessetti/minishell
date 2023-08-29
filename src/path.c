/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:15:47 by pedro             #+#    #+#             */
/*   Updated: 2023/08/29 13:46:14 by annamarianu      ###   ########.fr       */
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
		ft_printf(RED "minishell: %s: command not found\n" RESET,
			cmd[0]);
	// free(cmd);
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

t_cmd_tb	*choose_handle(char *cmd, char **envp, t_cmd_tb *list, char **args)
{
	char	**possible_paths;

	// Absolute path
	if (ft_isdir(cmd))
	{
		if (access(list->path, F_OK) == -1)
			ft_printf(RED "minishell: %s: No such file or directory\n" RESET,
				args[0]);
		list = set_cmd_tb_list(list,args[0], args);
	}
	else
	{
		possible_paths = set_possible_paths(envp);
		list = find_path(list, possible_paths, cmd, args);
		free_matrix(possible_paths);
	}
	return (list);
}

/*Main function to define if the argv is an absolute path or not*/
// t_cmd_tb	*define_path(t_cmd_tb *list, char *buf, char **envp, char **args)
// {
// 	char	*var;

// 	var = NULL;
// 	if (ft_str_empty(buf))
// 		list = handle_str_error(buf, list);
// 	if ((var = ft_strnstr(buf, "$", ft_strlen(buf))))
// 	{
// 		var = handle_variable(var, envp);
// 		if (!var)
// 			return list = NULL;
// 		list = choose_handle(++var, envp, list,args);
// 	}
// 	else
// 		list = choose_handle(buf, envp, list,args);
// 	return (list);
// }
