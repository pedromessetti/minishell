/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:57:33 by pmessett          #+#    #+#             */
/*   Updated: 2023/05/29 11:52:47 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates memory for an array of nmemb elements of size bytes each
and returns a pointer to the  allocated memory.  The memory is set
to zero. If nmemb or size is 0, then calloc() returns either NULL,
or a unique pointer value that can later be successfully passed to
free()*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc_space;

	alloc_space = (void *)malloc(nmemb * size);
	if (!alloc_space)
		return (NULL);
	ft_memset(alloc_space, 0, (nmemb * size));
	return (alloc_space);
}
