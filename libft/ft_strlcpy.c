/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:40:10 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:46 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	unsigned int	src_len;
	unsigned int	i;

	i = 0;
	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
