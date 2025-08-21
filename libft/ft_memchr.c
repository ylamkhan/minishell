/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:36:23 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:38:45 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		if (*str == (char)c)
			return (str);
		str++;
		i++;
	}
	return (0);
}
