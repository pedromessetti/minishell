/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:34:36 by annamarianu       #+#    #+#             */
/*   Updated: 2023/10/15 12:34:46 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (c);
// 	return (0);
// }

// int	exit_error(char *str)
// {
// 	char	*temp;

// 	temp = ft_strjoin("exit: ", str);
// 	temp = free_joined(temp, ft_strdup(": numeric argument required"));
// 	ft_putendl_fd(temp, STDERR_FILENO);
// 	free(temp);
// 	return (1);
// }

// unsigned long long	ft_atoll(char *str)
// {
// 	unsigned long long	res;
// 	int					i;

// 	res = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] > 47 && str[i] < 58)
// 		{
// 			res = (res * 10) + (str[i] - '0');
// 			i++;
// 		}
// 	}
// 	return (res);
// }

// unsigned char	check_number(char *str)
// {
// 	unsigned long long	n;
// 	int					s;
// 	int					i;

// 	s = 1;
// 	i = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 		if (str[i++] == '-')
// 			s = -1;
// 	n = ft_atoll(&str[i]);
// 	if (((ft_strlen(str) > 19 && s > 0) || (ft_strlen(str) > 20 && s < 0))
// 		|| ((n > LLONG_MAX && s > 0) || (n - 1 > LLONG_MAX && s < 0)))
// 	{
// 		s = 1;
// 		n = 2;
// 		exit_error(str);
// 	}
// 	return ((unsigned char)((long long)(n * s)));
// }

// int	check_exit_arg(char *str)
// {
// 	int		i;

// 	i = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	while (ft_isdigit(str[i]))
// 		i++;
// 	if (str[i])
// 		return (exit_error(str));
// 	return (0);
// }

