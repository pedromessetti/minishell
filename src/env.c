/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:59:24 by pedro             #+#    #+#             */
/*   Updated: 2023/09/08 00:06:22 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_env(char **envp)
{
	int	fd;
	int	i;

	fd = open(".env", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], fd);
		i++;
	}
	close(fd);
	return (0);
}

char	*ft_getenv(char *name)
{
	int		fd;
	char	*line;
	char	*value;

	value = NULL;
	fd = open(".env", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, name, ft_strlen(name)) == 0)
		{
			close(fd);
			value = ft_strchr(line, '=');
			value++;
			value[ft_strlen(value) - 1] = '\0';
			free(line);
			return (value);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (NULL);
}

char	**get_full_env(void)
{
	int		fd;
	char	*line;
	char	**env;
	int		i;

	fd = open(".env", O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	env = malloc(sizeof(char *) * (i + 1));
	fd = open(".env", O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		env[i] = ft_strdup(line);
		i++;
		line = get_next_line(fd);
	}
	env[i] = NULL;
	close(fd);
	return (env);
}
