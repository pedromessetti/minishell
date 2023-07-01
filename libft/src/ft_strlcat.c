/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:53:01 by pmessett          #+#    #+#             */
/*   Updated: 2023/05/29 15:02:44 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Concatenate src string and dst string. It will append at most
size - strlen(dst) - 1 bytes, NULL-terminating the result.

Returns the initial length of dst plus the length of src.*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i_src;
	unsigned int	i_dst;
	unsigned int	dst_len;
	unsigned int	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i_src = 0;
	i_dst = dst_len;
	if (size == 0 || size <= dst_len)
		return (src_len + size);
	while (src[i_src] && (i_src < (size - dst_len - 1)))
		dst[i_dst++] = src[i_src++];
	dst[i_dst] = '\0';
	return (src_len + dst_len);
}
