/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:16:23 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:16:24 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Verify if the string only contains numeric chars

Return 1 if only contains num chars
Return 0 if contains other chars*/
int	ft_str_is_num(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		if (!ft_isnum(s[i]))
			return (0);
	return (1);
}
