/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:07:12 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/03 17:07:18 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	count_quotes(char *s)
{
	int	i;
	int	count;
	int	dq;
	int	sq;

	i = 0;
	count = 0;
	dq = 0;
	sq = 0;
	while (s[i])
	{
		sq = (sq + (!dq && s[i] == '\'')) % 2;
		dq = (dq + (!sq && s[i] == '"')) % 2;
		if ((!sq && s[i] == '"') || (!dq && s[i] == '\''))
			count++;
		i++;
	}
	if (sq || dq)
		return (-1);
	return (count);
}

char	*ft_del(char *s, int sq, int dq)
{
	int		i;
	int		j;
	char	*str;

	j = -1;
	i = 0;
	if (!s || (count_quotes(s) == -1))
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) - count_quotes(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		sq = (sq + (!dq && s[i] == '\'')) % 2;
		dq = (dq + (!sq && s[i] == '"')) % 2;
		if ((s[i] != '"' || sq) && (s[i] != '\'' || dq) && ++j >= 0)
			str[j] = s[i];
		i++;
	}
	str[++j] = '\0';
	return (str);
}
