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
			|| str[i] == '.' || str[i] == ',' || (str[i] == '?' && i == 1) || ft_isdigit(str[i - 1]))
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
	char	*value;
	while (env)
	{
		if (!ft_strncmp(str, env->content, ft_strlen(str)))
			break ;
		env = env->next;
	}
	if (!env)
		return (ft_strdup(""));
	value = ft_strdup(env->content + ft_strlen(str) + 1);
	free(str);
	return (value);
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

void	forbidden_print(int flag, char *str)
{
	char	*temp;

	temp = 0;
	if (flag == 1)
	{
		temp = ft_strjoin("Forbidden sequence of characters detected: '", str);
		temp = free_joined(temp, ft_strdup("'"));
	}
	else if (flag == 2)
	{
		temp = ft_substr(str, 0, 1);
		temp = free_joined(ft_strdup("Forbidden character detected: '"), temp);
		temp = free_joined(temp, ft_strdup("'"));
	}
	ft_putendl_fd(temp, STDERR_FILENO);
	if (temp)
		free(temp);
}

int	ft_isforbidden_char(char *str)
{
	if (str[0] && (str[0] == '\\' || str[0] == '`' || str[0] == '['
			|| str[0] == ']' || str[0] == ';' || str[0] == '#'
			|| str[0] == '{' || str[0] == '}'))
	{
		forbidden_print(2, str);
		return (set_exit_code(1, true));
	}
	if (str[0] && ((str[0] == '(' && str[1] == ')')
			|| (str[0] == '<' && str[1] == '&')
			|| (str[0] == '>' && str[1] == '&')
			|| (str[0] == '&' && str[1] == '>')
			|| (str[0] == '$' && str[1] == '(')
			|| (str[0] == ')' && str[1] == '$')
			|| (str[0] == '[' && str[1] == ']')
			|| (str[0] == '&' && str[1] == '&')
			|| (str[0] == '|' && str[1] == '|')))
	{
		forbidden_print(1, &str[0]);
		return (set_exit_code(1, true));
	}
	return (0);
}