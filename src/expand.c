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
	{
		var = search_var(var, env);
	}
	return (var);
}


char	*ft_expansion(char *str, char state, t_env *env)
{
	int		i;
	char	*s;
	char	*tmp;

	s = ft_strdup(str);

	i = 0;	
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!state)
				state = str[i];
			else if (state == str[i])
				state = '\0';
		}
		if (state == '\'' || str[i] != '$')
		{
			i++;
			continue;
		}
		tmp = ft_substr(s, 0, i);
		free(s);
		
		tmp = free_joined(tmp, expand_dollar(str, &i, env));
		
		s = free_joined(tmp, ft_substr(str, i, ft_strlen(str)));
		
	}
	free(str);
	return (s);
}