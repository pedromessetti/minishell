/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:48:44 by pmessett          #+#    #+#             */
/*   Updated: 2024/03/15 00:20:48 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_literal_string(char *str, int len)
{
	if (len < 2)
		return (0);
	if ((str[0] == '"' || str[len - 1] == '"') || (str[0] == '\'' \
			|| str[len - 1] == '\''))
		return (1);
	return (0);
}

int	is_keyword(char *str, int len)
{
	if (len == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (1);
	if (len == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (1);
	if (len == 6 && ft_strncmp(str, "export", 6) == 0)
		return (1);
	if (len == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (1);
	if (len == 4 && ft_strncmp(str, "echo", 4) == 0)
		return (1);
	if (len == 3 && ft_strncmp(str, "env", 3) == 0)
		return (1);
	if (len == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	return (0);
}
