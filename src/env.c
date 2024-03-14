/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:50:01 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/14 23:57:24 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
Sets environment variables in env linked list.

@param var string that represents an environment variable.
@param env double pointer to a linked list of environment variables.
*/
void	set_env(char *var, t_env **env)
{
	char	*trimmed_var;
	char	*tmp_var;

	trimmed_var = ft_strtrim(var, "'\"");
	tmp_var = ft_substr(trimmed_var, 0, ft_strlen(trimmed_var)
			- ft_strlen(ft_strchr(trimmed_var, '=')));
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
	else if (!is_valid_identifier(trimmed_var))
		ft_printf("minishell: export: `%s': not a valid identifier\n",
			trimmed_var);
	free(trimmed_var);
	free(tmp_var);
}

/**
Removes an environment variable from env linked list.

@param var pointer to a character array that represents the name of the
environment variable to be unset.
@param env pointer to a pointer to a linked list of environment variables.
*/
void	unset_env(char *var, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	if (!is_valid_identifier(var))
	{
		ft_printf("minishell: unset: `%s': not a valid identifier\n", var);
		return ;
	}
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

/**
Searches for an environment variable with the given name and returns its
value.

@param name environment variable to be retrieved.
@param env pointer to a linked list of `t_env` structures.
Each `t_env` structure represents an environment variable and
contains a `content` field that stores the variable name and value
in the format "name=value".

@return a pointer to a character array (string) that represents the
value of the environment variable with the given name.
If the environment variable is found, the function returns the value
of the variable. If the environment variable is not found,
the function returns NULL.
*/
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

/**
Takes a linked list of environment variables and returns an array of
strings containing the full environment.

@param env pointer to a pointer to a structure of type `t_env`.
*/
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
		full_env[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	full_env[i] = NULL;
	return (full_env);
}

/**
Prints the content of env linked list to specified fd.

@param list linked list of environment variables.
@param fd integer representing the file descriptor. It is used to specify
the file or output stream where the environment variables will be printed.
*/
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
