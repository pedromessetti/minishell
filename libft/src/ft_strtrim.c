/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:15:46 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:15:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates memory with malloc() and returns a copy of
s1 with the characters specified in ’set’ removed
from the beginning and the end of the string,
or NULL if the allocation fails.*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	strim = ft_substr(s1, start, (end - start));
	return (strim);
}
