/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:20:58 by pedro             #+#    #+#             */
/*   Updated: 2023/09/07 23:20:59 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base_is_possible(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	ft_converter(long int n, int baselen, char *base, int fd)
{
	if (n / baselen == 0)
		ft_putchar_fd(base[n % baselen], fd);
	else
	{
		ft_converter(n / baselen, baselen, base, fd);
		ft_putchar_fd(base[n % baselen], fd);
	}
}

/*Outputs the integer ’n’ converted to any base passed as
argument to the given file descriptor.*/
void	ft_putnbr_base_fd(int nbr, char *base, int fd)
{
	long int	n;
	int			baselen;

	n = nbr;
	baselen = 0;
	while (base[baselen])
	{
		if (base[baselen] == '+' || base[baselen] == '-')
			return ;
		baselen++;
	}
	if (baselen <= 1)
		return ;
	if (ft_base_is_possible(base))
		return ;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	ft_converter(n, baselen, base, fd);
}
