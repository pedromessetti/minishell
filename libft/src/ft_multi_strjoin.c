/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:15:16 by pedro             #+#    #+#             */
/*   Updated: 2023/06/18 15:39:20 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calculate_total_length(va_list args)
{
	size_t		total_len;
	const char	*str;

	total_len = 0;
	str = va_arg(args, const char *);
	while (str)
	{
		total_len += ft_strlen(str);
		str = va_arg(args, const char *);
	}
	return (total_len);
}

static void	copy_strings_with_delimiters(char *result, va_list args,
		const char *delimiter, size_t total_len)
{
	char		*ptr;
	const char	*str;
	size_t		len;
	size_t		i;

	ptr = result;
	i = 0;
	str = va_arg(args, const char *);
	while (str)
	{
		len = ft_strlen(str);
		ft_memcpy(ptr, str, len);
		ptr += len;
		if (i < total_len - 1 && delimiter != NULL)
		{
			ft_memcpy(ptr, delimiter, ft_strlen(delimiter));
			ptr += ft_strlen(delimiter);
		}
		str = va_arg(args, const char *);
		i++;
	}
	if (total_len > 0)
		ptr -= ft_strlen(delimiter);
	*ptr = '\0';
}

char	*ft_multi_strjoin(const char *delimiter, ...)
{
	va_list	args;
	size_t	total_len;
	char	*result;
	size_t	total_delimiter_len;

	va_start(args, delimiter);
	total_len = calculate_total_length(args);
	va_end(args);
	total_delimiter_len = ft_strlen(delimiter) * (total_len - 1);
	result = (char *)malloc(total_len + total_delimiter_len + 1);
	if (!result)
		return (NULL);
	va_start(args, delimiter);
	copy_strings_with_delimiters(result, args, delimiter, total_len);
	va_end(args);
	return (result);
}
