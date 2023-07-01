/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:48:31 by pmessett          #+#    #+#             */
/*   Updated: 2023/05/29 11:46:58 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Erases the data in the n bytes of the memory
starting at the location pointed to by s, by writing
zeros (bytes containing '\0') to that area.*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
