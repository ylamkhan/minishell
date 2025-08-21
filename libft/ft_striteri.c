/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:39:50 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:52 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (i < ft_strlen(s))
	{
		f(i, &s[i]);
		i++;
	}
}
