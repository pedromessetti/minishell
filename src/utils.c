/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:48:00 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 10:31:08 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(char *s)
{
	if (ft_strnstr(s, "|", ft_strlen(s)))
		return (1);
	return (0);
}

int	has_redirections(char *s)
{
	if (ft_strnstr(s, "<", ft_strlen(s)) || ft_strnstr(s, ">", ft_strlen(s)))
		return (1);
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

char	*ft_strip(char *str)
{
	size_t	len;
	char	*result;
	size_t	l_trim;
	size_t	r_trim;
	size_t	trimmed_lenght;

	len = ft_strlen(str);
	result = str;
	l_trim = -1;
	while (ft_isspace(result[++l_trim]))
		;
	r_trim = len - 1;
	while (r_trim > l_trim && ft_isspace(result[--r_trim]))
		;
	if (l_trim > 0 || r_trim < len - 1)
	{
		trimmed_lenght = r_trim - l_trim + 1;
		ft_memmove(result, result + l_trim, trimmed_lenght);
		result[trimmed_lenght] = '\0';
	}
	size_t i, j;
	for (i = 0, j = 0; result[i]; i++)
	{
		if (result[i] == '\n')
			i++;
		if (ft_isspace(result[i]))
		{
			if (j == 0 || !ft_isspace(result[j - 1]))
				result[j++] = ' ';
		}
		else
			result[j++] = result[i];
	}
	result[j] = '\0';
	return (result);
}
