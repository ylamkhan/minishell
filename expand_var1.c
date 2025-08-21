/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:11:37 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/06 19:24:35 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_strchars_i(const char *s, char *set)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || str[i
					- 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

char	*join_all(char **args)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	i = 0;
	tmp1 = NULL;
	while (args && args[i])
	{
		tmp = ft_strjoin(tmp1, args[i]);
		if (tmp1)
			free(tmp1);
		tmp1 = ft_strjoin(tmp, " ");
		free(tmp);
		i++;
	}
	return (tmp1);
}
