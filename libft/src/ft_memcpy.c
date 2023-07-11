/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:57:12 by pmessett          #+#    #+#             */
/*   Updated: 2023/06/18 14:08:09 by pmessett            ###   ########.fr       */
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
