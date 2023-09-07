/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:14:53 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:14:55 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copies n bytes from memory area src to
memory area dest.

Returns a pointer to dest.*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*memsrc;
	char		*memdest;

	if (!dest && !src)
		return (NULL);
	i = -1;
	memsrc = (const char *)src;
	memdest = (char *)dest;
	while (++i < n)
		memdest[i] = memsrc[i];
	return (dest);
}
