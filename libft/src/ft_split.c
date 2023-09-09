/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:21:05 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:21:06 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mem(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			j = 1;
			i++;
		}
		else if (*s == c)
			j = 0;
		s++;
	}
	return (i);
}

static char	*ft_string(char const *s, char *new_s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	new_s = malloc(sizeof(char) * i + 1);
	if (!new_s || !s)
		return (NULL);
	i = -1;
	while (s[++i] && s[i] != c)
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}

/*Allocates memory with malloc() and returns an array
of strings obtained by splitting str s using the
char c as a delimiter, or NULL if the allocation fails.
The array ends with a NULL pointer.*/
char	**ft_split(char const *s, char c)
{
	char	**new_s;
	int		i;
	int		j;

	if (!*s)
		return (NULL);
	new_s = (char **)malloc((ft_mem(s, c) + 1) * sizeof(char **));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			new_s[j] = ft_string((char *)s + i, new_s[j], c);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	new_s[j] = 0;
	return (new_s);
}
