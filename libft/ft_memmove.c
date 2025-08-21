/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:36:49 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:42:05 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_c;
	char	*src_c;

	src_c = (char *)src;
	dst_c = (char *)dst;
	if (src_c == dst_c)
		return (src_c);
	if (!src_c && !dst_c)
		return (NULL);
	if (dst_c < src_c)
		ft_memcpy(dst_c, src_c, len);
	else
	{
		while (len)
		{
			dst_c[len - 1] = src_c[len - 1];
			len--;
		}
	}
	return (dst_c);
}
