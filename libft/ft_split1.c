/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 04:03:33 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/05 04:25:02 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	you_f1(char *str, int *i)
{
	if (str[*i] == '"')
	{
		i++;
		while (str[*i] != '"' && str[*i])
			i++;
	}
}

void	you_f2(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		i++;
		while (str[*i] != '\'' && str[*i])
			i++;
	}
}

int	count_words(char *str, char c)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 1;
	i = 0;
	while (str && str[i])
	{
		you_f1(str, &i);
		you_f2(str, &i);
		if (str[i] != c && j)
		{
			count++;
			j = 0;
		}
		if (str[i] == c)
			j = 1;
		i++;
	}
	return (count);
}
