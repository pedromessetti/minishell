/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:16:46 by pmessett          #+#    #+#             */
/*   Updated: 2023/07/11 08:37:26 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Find the correct path by tryng to acess all the possible paths*/
t_cmd	*find_multiple_path(t_cmd *path_list, char **possible_paths, char *av,
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

t_cmd	*choose_multiple_handle(char *av, char **envp, t_cmd *path_list)
{
	char	**p_f;
	char	**possible_paths;

	p_f = ft_split(av, ' ');
	if (ft_isdir(av))
	{
		if (access(p_f[0], F_OK) == -1)
			ft_printf(RED "minishell: %s: No such file or directory\n" RESET,
				p_f[0]);
		path_list = set_cmd_list(path_list, p_f[0], p_f);
	}
	else
	{
		possible_paths = set_possible_paths(envp);
		path_list = find_multiple_path(path_list, possible_paths, av,
			p_f);
		free_matrix(possible_paths);
	}
	return (path_list);
}

/*Main function to define if the argv is an absolute path or not*/
t_cmd	*define_multiple_path(t_cmd *list, char **av, char **envp)
{
	int		i;
	char	*var;

	i = -1;
	var = NULL;
	while (av[++i])
	{
		if (ft_str_empty(av[i]))
			list = handle_str_error(av[i], list);
		if ((var = ft_strnstr(av[i], "$", ft_strlen(av[i]))))
		{
			var = handle_variable(var, envp);
			list = choose_handle(var, envp, list);
		}
		else
			list = choose_multiple_handle(av[i], envp, list);
	}
	return (list);
}
