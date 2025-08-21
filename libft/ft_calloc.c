/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:32:52 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:37:46 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if ((size > 0) && (count > SIZE_MAX / size))
		return (NULL);
	str = (char *)malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
