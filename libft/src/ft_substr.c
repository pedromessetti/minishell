/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:19:38 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:19:39 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates memory with malloc() and returns a substring
from the str s. The substring begins at index ’start’ and
is of maximum size len.*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (0);
	if (len == 0 || start > ft_strlen(s))
	{
		subs = malloc(1);
		*subs = '\0';
		return (subs);
	}
	if (ft_strlen(s) - start < len)
		subs = malloc(ft_strlen(s) - start + 1);
	else
		subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		subs[i++] = s[start++];
	subs[i] = '\0';
	return (subs);
}
