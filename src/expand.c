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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}

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

char	*remove_quotes(char *tk, t_env *env)
{
	int		i;
	int		j;
	char	*s;
	char	*temp;

	i = 0;
	j = 0;
	s = ft_strdup("");
	temp = 0;
	while (i < (int)ft_strlen(tk))
	{
		j += skip_quotes(&tk[i]);
		if (tk[i] == '\'' || tk[i] == '\"')
			temp = ft_expansion(ft_substr(tk, i + 1, (j - i - 1)), tk[i], env);
		else
			temp = ft_expansion(ft_substr(tk, i, (j - i + 1)), tk[i], env);
		s = free_joined(s, temp);
		i = ++j;
	}
	free(tk);
	return (s);
}

int	skip_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '\'' && str[0] != '\"')
	{
		while (str[i + 1] && str[i] != '\'' && str[i] != '\"')
			i++;
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i--;
	}
	else
	{
		while (str[++i] && str[i] != str[0])
			continue ;
	}
	return (i);
}