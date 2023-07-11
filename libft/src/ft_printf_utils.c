/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:31:17 by pmessett             #+#    #+#             */
/*   Updated: 2023/06/18 10:54:26 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, unsigned int *size)
{
	*size += 1;
	write(1, &c, 1);
}

void	ft_putstr(char *s, unsigned int *size)
{
	unsigned int	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)", size);
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], size);
		i++;
	}
}

void	ft_putnbr(int n, unsigned int *size)
{
	if (n == -2147483648)
	{
		ft_putchar('-', size);
		ft_putchar('2', size);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-', size);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr((n / 10), size);
		ft_putnbr((n % 10), size);
	}
	else
		ft_putchar((n + 48), size);
}

void	ft_putunsnbr(unsigned int n, unsigned int *size)
{
	if (n >= 10)
	{
		ft_putunsnbr((n / 10), size);
		ft_putunsnbr((n % 10), size);
	}
	else
		ft_putchar((n + 48), size);
}

void	ft_putnbr_base(unsigned int n, char *base, unsigned int *size)
{
	long int	li;
	int			baselen;

	li = n;
	baselen = 0;
	while (base[baselen])
		baselen++;
	if (li / baselen == 0)
		ft_putchar(base[li % baselen], size);
	else
	{
		ft_putnbr_base(li / baselen, base, size);
		ft_putchar(base[li % baselen], size);
	}
}
