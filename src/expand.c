/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aangelic <aangelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:51:01 by aangelic          #+#    #+#             */
/*   Updated: 2023/10/10 19:02:50 by aangelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(char *str, int *i, t_env *env)
{
	char	*var;
	char	*exit_code;
	int		index;

	index = *i;
	var = separate_var(&str[index]);
	if (!ft_strcmp(var, "$"))
		*i += 1;
	else
		*i += ft_strlen(var) + 1;
	if (!ft_strcmp(var, "?"))
	{
		exit_code = ft_itoa(set_exit_code(0, false));
		free(var);
		var = exit_code;
	}
	else if (ft_strcmp(var, "$"))
		var = search_var(var, env);
	return (var);
}


char	*ft_expansion(char *str, char c, t_env *env)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	if (!ft_strcmp(str, "$"))
		return (str);
	s = ft_strdup("");
	while (str[j])
	{
		i = j;
		if (c != '\'' && str[i] == '$') {
			s = free_joined(s, expand_dollar(str, &i, env));
			if (ft_strnstr(s, "=", ft_strlen(s)))
				s = ft_strnstr(s, "=", ft_strlen(s)) + 1;
		}
		else
		{
			while (str[++i] && str[i] != '$')
				continue ;
			s = free_joined(s, ft_substr(str, j, (i - j)));
		}
		j = i;
	}
	free(str);
	return (s);
}