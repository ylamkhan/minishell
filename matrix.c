/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:06:30 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 05:48:58 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}

void	funcfree(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		free(a[i++]);
	if (a)
		free(a);
}

int	ft_matrixlen(char **t)
{
	int	i;

	i = 0;
	while (t && t[i])
		i++;
	return (i);
}

char	**ft_update_matrix(char **env, char *s)
{
	char	**new;
	int		len;
	int		i;

	new = NULL;
	i = -1;
	if (!s)
		return (env);
	len = ft_matrixlen(env);
	new = malloc(sizeof(char *) * (len + 2));
	new[len + 1] = NULL;
	if (!new)
		return (env);
	while (++i < len)
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
		{
			funcfree(env);
			funcfree(new);
		}
	}
	new[i] = ft_strdup(s);
	funcfree(env);
	return (new);
}

char	**ft_dup_matrix(char **s)
{
	char	**new_str;
	int		n;
	int		i;

	i = 0;
	n = ft_matrixlen(s);
	new_str = malloc(sizeof(char *) * (n + 1));
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = ft_strdup(s[i]);
		if (!new_str[i])
		{
			ft_free_matrix(&new_str);
			return (NULL);
		}
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}
