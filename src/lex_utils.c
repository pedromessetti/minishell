/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:48:00 by pedro             #+#    #+#             */
/*   Updated: 2023/09/08 00:45:16 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_literal_string(char *str, int len)
{
	if (len < 2)
		return (0);
	if ((str[0] == '"' || str[len - 1] == '"') || (str[0] == '\'' || str[len
			- 1] == '\''))
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
	return (0);
}
