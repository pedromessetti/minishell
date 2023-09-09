/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:21:44 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:21:46 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a pointer to  the matched character
or NULL if the character is not found.*/
char	*ft_strrchr(const char *s, int c)
{
	unsigned char	a;
	int				i;

	a = c;
	i = ft_strlen(s);
	if (a == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == a)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
