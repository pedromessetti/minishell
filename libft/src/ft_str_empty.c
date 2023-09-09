/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:19:31 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:19:32 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Return 1 if the str is empty or has only spaces or tabs
Return 0 if the str has other chars*/
int	ft_str_empty(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
	}
	return (1);
}
