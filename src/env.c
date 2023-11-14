/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:50:01 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/14 11:25:03 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char *var, t_env **env)
{
	char	*trimmed_var;
	trimmed_var = ft_strtrim(var, "'\"");
	char *tmp_var = ft_substr(trimmed_var, 0, ft_strlen(trimmed_var)-ft_strlen(ft_strchr(trimmed_var, '=')));
	if (!*env)
		*env = add_env_node(trimmed_var);
	else if (ft_strchr(trimmed_var, '=') && ft_strlen(trimmed_var) > 1
		&& ft_getenv(tmp_var, env))
	{
		unset_env(tmp_var, env);
		add_env_tail(env, add_env_node(trimmed_var));
	}
	else if (ft_strchr(trimmed_var, '=') && ft_strlen(trimmed_var) > 1)
		add_env_tail(env, add_env_node(trimmed_var));
	else
		ft_printf("minishell: export: `%s': not a valid identifier\n",
			trimmed_var);
	free(trimmed_var);
	free(tmp_var);
}

void	unset_env(char *var, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, ft_strlen(var)) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*ft_getenv(char *name, t_env **env)
{
	char	*value;
	t_env	*tmp;

	value = NULL;
	tmp = *env;
	if (name[0] == '$')
		name++;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
		{
			value = ft_strchr(tmp->content, '=');
			value++;
			value[ft_strlen(value)] = '\0';
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_full_env(t_env **env)
{
	int		i;
	char	**full_env;
	t_env	*tmp;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	full_env = (char **)malloc(sizeof(char *) * (i + 1));
	tmp = *env;
	i = 0;
	if (!full_env)
		return (NULL);
	while (tmp)
	{
		full_env[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	full_env[i] = NULL;
	return (full_env);
}

/*Print env*/
void	print_env(t_env **list, int fd)
{
	t_env	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp)
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
}
