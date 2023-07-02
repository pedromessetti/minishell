/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:16:46 by pmessett          #+#    #+#             */
/*   Updated: 2023/07/01 11:00:54 by pedro            ###   ########.fr       */
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
t_cmd	*find_path(t_cmd *path_list, char **possible_paths, char *av,
		char **path_and_cmd)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (possible_paths[++i])
	{
		tmp = ft_multi_strjoin("/", possible_paths[i], path_and_cmd[0], NULL);
		if (!access(tmp, F_OK))
			break ;
		if (possible_paths[i + 1])
			free(tmp);
	}
	if (!tmp || (!possible_paths[i] && !check_builtin(av)))
		ft_printf(RED"minishell: %s: command not found\n"RESET, path_and_cmd[0]);
	free(path_and_cmd[0]);
	path_and_cmd[0] = tmp;
	path_list = set_cmd_list(path_list, path_and_cmd[0], path_and_cmd);
	return (path_list);
}

t_cmd	*handle_str_error(char *buf, t_cmd *path_list)
{
	ft_printf("minishell: %s: command not found\n", buf);
	path_list = set_cmd_list(path_list, NULL, NULL);
	return (path_list);
}

t_cmd	*choose_handle(char *buf, char **envp, t_cmd *list)
{
	char	**path_and_cmd;
	char	**possible_paths;

	path_and_cmd = ft_split(buf, ' ');
	if (is_dir(buf))
	{
		if (access(path_and_cmd[0], F_OK) == -1)
			ft_printf("minishell: %s: No such file or directory\n", path_and_cmd[0]);
		list = set_cmd_list(list, path_and_cmd[0], path_and_cmd);
	}
	else
	{
		possible_paths = set_possible_paths(envp);
		list = find_path(list, possible_paths, buf, path_and_cmd);
		free_matrix(possible_paths);
	}
	return (list);
}

/*Main function to define if the argv is an absolute path or not*/
t_cmd	*define_path(t_cmd *list, char *buf, char **envp)
{
	if (ft_str_empty(buf))
		list = handle_str_error(buf, list);
	else
		list = choose_handle(buf, envp, list);

	list->pid = fork();
	if (list->pid == 0)
		child_process(list, envp);
	waitpid(list->pid, NULL, 0);
	free_path_list(&list);
	return (list);
}
