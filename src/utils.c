/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:08:46 by pmessett             #+#    #+#             */
/*   Updated: 2023/07/07 08:18:28 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(char *s)
{
	if (ft_strnstr(s, "|", ft_strlen(s)))
		return (1);
	return (0);
}

int	has_redirections(char *s)
{
	if (ft_strnstr(s, "<", ft_strlen(s)) || ft_strnstr(s, ">", ft_strlen(s)))
		return (1);
	return (0);
}

char	*ft_strip(char *str)
{
	size_t	len;
	char	*result;
	size_t	l_trim;
	size_t	r_trim;
	size_t	trimmed_lenght;

	len = ft_strlen(str);
	result = str;
	l_trim = -1;
	while (ft_isspace(result[++l_trim]))
		;
	r_trim = len - 1;
	while (r_trim > l_trim && ft_isspace(result[--r_trim]))
		;
	if (l_trim > 0 || r_trim < len - 1)
	{
		trimmed_lenght = r_trim - l_trim + 1;
		ft_memmove(result, result + l_trim, trimmed_lenght);
		result[trimmed_lenght] = '\0';
	}
	size_t i, j;
	for (i = 0, j = 0; result[i]; i++)
	{
		if (result[i] == '\n')
			i++;
		if (ft_isspace(result[i]))
		{
			if (j == 0 || !ft_isspace(result[j - 1]))
				result[j++] = ' ';
		}
		else
			result[j++] = result[i];
	}
	result[j] = '\0';
	return (result);
}

void	print_list(t_cmd *list)
{
	t_cmd *curr;

	curr = list;
	while (curr)
	{
		for (int i = 0; curr->p_f[i]; i++)
			printf("p_f[%i] = %s\n", i, curr->p_f[i]);
		curr = curr->next;
	}
}