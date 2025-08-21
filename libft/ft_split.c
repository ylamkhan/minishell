/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:39:33 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/05 04:05:12 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_set(const char *str, char set, int i)
{
	while (str[i] && str[i] == set)
		i++;
	return (i);
}

static int	count_non_set(const char *str, char set, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' && str[i])
			i++;
		i++;
	}
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		i++;
	}
	while (str[i] && str[i] != set)
		i++;
	return (i);
}

static int	free_str(char **ret, int d)
{
	int	i;

	i = 0;
	if (!ret[d])
	{
		while (ret[i])
		{
			free(ret[i]);
			i++;
		}
		free(ret);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *str, char set)
{
	int		j;
	int		i;
	int		len;
	char	**ret;
	int		start;

	j = 0;
	i = 0;
	len = count_words((char *)str, set);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (str && str[i])
	{
		start = count_set(str, set, i);
		i = count_non_set(str, set, start);
		if (len > j)
		{
			ret[j] = ft_substr(str, start, i - start);
			if (!free_str(ret, j++))
				return (NULL);
		}
	}
	ret[j] = NULL;
	return (ret);
}
