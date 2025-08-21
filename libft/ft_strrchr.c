/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:40:51 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:40 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*a;
	int				i;

	i = 0;
	a = (unsigned char *)s;
	while (a[i])
		i++;
	while (i >= 0)
	{
		if (a[i] == (unsigned char)c)
			return ((char *)(&a[i]));
		i--;
	}
	return (0);
}
