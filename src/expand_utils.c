/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aangelic <aangelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:12:55 by aangelic          #+#    #+#             */
/*   Updated: 2023/10/10 19:01:21 by aangelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This fuction isolates the variable name */
char	*separate_var(char *str)
{
	char	*var;
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '$' || str[i] == '*' || str[i] == 32 || str[i] == ':'
			|| str[i] == '\'' || str[i] == '\"' || str[i] == '/'
			|| str[i] == '.' || str[i] == ',' || (str[i] == '?' && i == 1))
			break ;
	}
	if (i == 1 && str[i - 1] == '$' && str[i] != '?')
		var = ft_strdup("$");
	else if (i == 1 && str[i])
		var = ft_substr(str, 1, i);
	else
		var = ft_substr(str, 1, (i - 1));
	return (var);
}

char	*search_var(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(str, env->content, ft_strlen(str)))
			break ;
		env = env->next;
	}
	free(str);
	if (!env)
		return (ft_strdup(""));
	str = ft_strdup(env->content);
	return (str);
}

char	*free_joined(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
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

/* Function to skip characters between quotes
or to skip characters until a quotation mark is found */
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