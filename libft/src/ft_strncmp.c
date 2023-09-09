/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:20:12 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:20:17 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Compares only the first n bytes of s1 and s2.

Returns an integer less than, equal to, or greater than zero
if s1 is found, respectively, to be less than, to match,
or be greater than s2.*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
