/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:10:08 by pedro             #+#    #+#             */
/*   Updated: 2023/06/18 13:11:08 by pedro            ###   ########.fr       */
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
