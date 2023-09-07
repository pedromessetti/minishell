/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:57:52 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:37:45 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (++i);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!s2[0])
		return (0);
	new_s = (char *)malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		new_s[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] != '\n' && s2[j])
		new_s[i++] = s2[j++];
	if (s2[j] == '\n')
		new_s[i++] = '\n';
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}

static int	ft_clear(char *s)
{
	size_t	i;
	size_t	j;
	int		is_new_line;

	i = 0;
	j = 0;
	is_new_line = 0;
	while (s[i])
	{
		if (is_new_line)
			s[j++] = s[i];
		if (s[i] == '\n')
			is_new_line = 1;
		s[i++] = '\0';
	}
	return (is_new_line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			read_bytes;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	line = gnl_strjoin(0, buf);
	if (ft_clear(buf))
		return (line);
	read_bytes = read(fd, buf, BUFFER_SIZE);
	if (read_bytes < 0)
	{
		free(line);
		return (NULL);
	}
	while (read_bytes)
	{
		line = gnl_strjoin(line, buf);
		if (ft_clear(buf))
			break ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
	}
	return (line);
}
