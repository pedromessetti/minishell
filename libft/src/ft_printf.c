/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:28:37 by pmessett          #+#    #+#             */
/*   Updated: 2023/06/18 10:52:37 by pmessett            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_checkflag(const char c, va_list args, unsigned int *size)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), size);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), size);
	else if (c == '%')
		ft_putchar('%', size);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), size);
	else if (c == 'u')
		ft_putunsnbr(va_arg(args, int), size);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), HEX_LOW, size);
	else if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), HEX_UP, size);
}

int	ft_printf(const char *s, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	size;

	size = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
			ft_checkflag(s[++i], args, &size);
		else
			ft_putchar(s[i], &size);
		i++;
	}
	va_end(args);
	return (size);
}
