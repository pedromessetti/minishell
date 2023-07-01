/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:33:11 by pmessett          #+#    #+#             */
/*   Updated: 2023/05/29 15:53:33 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Applies the function ’f’ to each char of the
str ’s’, and passing its index as first argument
to create a new str with malloc() resulting
from successive applications of ’f’.

Returns the new str created from the successive applications
of ’f’. NULL if the allocation fails.*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;

	i = 0;
	new_s = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new_s || !s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
