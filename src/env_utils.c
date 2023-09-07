/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:59:24 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 19:10:20 by pedro            ###   ########.fr       */
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
	char	*value = NULL;

	fd = open(".env", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, name, ft_strlen(name)) == 0)
		{
			close(fd);
			value = ft_strchr(line, '=');
			value++;
			value[ft_strlen(value) - 1] = '\0';  // Remove the new line at the end of value
			return (value);
		}
		line = get_next_line(fd);
		// free(line);
	}
	close(fd);
	return (NULL);
}