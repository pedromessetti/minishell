/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:14:13 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:14:15 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a pointer to the first occurrence of the char c in the str.*/
char	*ft_strchr(const char *s, int c)
{
	unsigned char	a;
	int				i;

	a = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return ((char *)s + i);
		i++;
	}
	if (a == '\0')
		return ((char *)s + i);
	return (NULL);
}
