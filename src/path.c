/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:15:47 by pedro             #+#    #+#             */
/*   Updated: 2023/07/15 06:58:45 by pedro            ###   ########.fr       */
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
		char **p_f)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	while (possible_paths[++i])
	{
		tmp = ft_multi_strjoin("/", possible_paths[i], p_f[0], NULL);
		if (!access(tmp, F_OK))
			break ;
		if (possible_paths[i + 1])
			free(tmp);
	}
	if (!tmp || (!possible_paths[i] && !check_builtin(av)))
		ft_printf(RED "minishell: %s: command not found\n" RESET,
			p_f[0]);
	free(p_f[0]);
	p_f[0] = tmp;
	path_list = set_cmd_list(path_list, p_f[0], p_f);
	return (path_list);
}

t_cmd	*handle_str_error(char *buf, t_cmd *path_list)
{
	ft_printf(RED "minishell: %s: command not found\n" RESET, buf);
	path_list = set_cmd_list(path_list, NULL, NULL);
	return (path_list);
}

t_cmd	*choose_handle(char *buf, char **envp, t_cmd *list)
{
	char	**p_f;
	char	**possible_paths;

	p_f = ft_split(buf, ' ');
	if (ft_isdir(buf))
	{
		if (access(p_f[0], F_OK) == -1)
			ft_printf(RED "minishell: %s: No such file or directory\n" RESET,
				p_f[0]);
		list = set_cmd_list(list, p_f[0], p_f);
	}
	else
	{
		possible_paths = set_possible_paths(envp);
		list = find_path(list, possible_paths, buf, p_f);
		free_matrix(possible_paths);
	}
	return (list);
}

/*Main function to define if the argv is an absolute path or not*/
t_cmd	*define_path(t_cmd *list, char *buf, char **envp)
{
	char	*var;

	var = NULL;
	if (ft_str_empty(buf))
		list = handle_str_error(buf, list);
	if ((var = ft_strnstr(buf, "$", ft_strlen(buf))))
	{
		var = handle_variable(var, envp);
		if (!var)
			return list = NULL;
		list = choose_handle(++var, envp, list);
	}
	else
		list = choose_handle(buf, envp, list);
	return (list);
}
