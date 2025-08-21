/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:40:04 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:48 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	lens;
	unsigned int	lend;
	unsigned int	i;

	lens = ft_strlen(src);
	if (!dst && !dstsize)
		return (lens);
	lend = ft_strlen(dst);
	i = 0;
	if (!dstsize || dstsize <= lend)
		return (dstsize + lens);
	while (src[i] && i < dstsize - lend - 1)
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	return (lens + lend);
}
