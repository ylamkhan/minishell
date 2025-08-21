/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 03:40:18 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 03:41:15 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ret_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i + 1);
}

int	end_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup1(char *s1)
{
	char	*a;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	a = (char *)malloc(i * sizeof(char) + 1);
	if (!a)
		return (0);
	i = -1;
	while (s1[++i])
		a[i] = s1[i];
	a[i] = '\0';
	return (a);
}
