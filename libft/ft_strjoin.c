/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:39:58 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 04:45:15 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a_len;
	int		b_len;
	int		i;
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	a_len = ft_strlen((char *)s1);
	b_len = ft_strlen((char *)s2);
	i = -1;
	ret = (char *)malloc(sizeof(char) * (a_len + b_len + 1));
	if (!ret)
		return (0);
	while (++i < a_len)
		ret[i] = s1[i];
	i = -1;
	while (++i < b_len)
		ret[a_len + i] = s2[i];
	ret[a_len + i] = '\0';
	return (ret);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i1;
	int		i2;
	char	*str;

	if (!s1)
		return (NULL);
	if (!s2)
		return (NULL);
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	str = (char *)malloc((i1 + i2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i1 = -1;
	while (s1 && s1[++i1])
		str[i1] = s1[i1];
	i2 = -1;
	while (s2 && s2[++i2])
		str[i1 + i2] = s2[i2];
	str[i1 + i2] = '\0';
	free(s1);
	return (str);
}
