/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:04:12 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/03 17:40:16 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*env_find_var(char *name, char **env)
{
	int	l_name;
	int	i;

	if (name == NULL || env == NULL)
		return (NULL);
	if (ft_strchr(name, '='))
		l_name = ft_strchr(name, '=') - name;
	else
		l_name = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], l_name) && env[i][l_name] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*env_get_value(char *name, char **env)
{
	char	*env_var;

	env_var = env_find_var(name, env);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	else
		return (NULL);
}

char	**ft_setenv(char *v, char *s, char **t, int i)
{
	int		a[2];
	char	*tab[2];

	if (i < 0)
		i = ft_strlen(v);
	a[0] = -1;
	tab[0] = ft_strjoin(v, "=");
	tab[1] = ft_strjoin(tab[0], s);
	free(tab[0]);
	while (!ft_strchr(v, '=') && t && t[++a[0]])
	{
		a[1] = i;
		if (a[1] < ft_strchr_i(t[a[0]], '='))
			a[1] = ft_strchr_i(t[a[0]], '=');
		if (!ft_strncmp(t[a[0]], v, a[1]))
		{
			tab[0] = t[a[0]];
			t[a[0]] = tab[1];
			free(tab[0]);
			return (t);
		}
	}
	t = ft_update_matrix(t, tab[1]);
	free(tab[1]);
	return (t);
}

char	*ft_getenv(char *v, char **env, int len)
{
	int	n;
	int	i;

	if (len < 0)
		len = ft_strlen(v);
	i = 0;
	while (!ft_strchr(v, '=') && env && env[i])
	{
		n = len;
		if (n < ft_strchr_i(env[i], '='))
			n = ft_strchr_i(env[i], '=');
		if (!ft_strncmp(env[i], v, n))
			return (ft_substr(env[i], n + 1, ft_strlen(env[i]) - 1));
		i++;
	}
	return (NULL);
}
