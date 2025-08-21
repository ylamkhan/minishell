/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:46 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 22:58:45 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	fun3(t_prompt **p, char *tmp, char *a)
{
	char	*tmp1;
	char	*v1;

	v1 = ft_getenv(tmp, (*p)->env, ft_strlen(tmp));
	if (!ft_strcmp(v1, "zinebismarriedtoyoussef"))
	{
		free(v1);
		v1 = NULL;
	}
	tmp1 = ft_strjoin(v1, a);
	if (v1)
		free(v1);
	(*p)->env = ft_setenv(tmp, tmp1, (*p)->env, ft_strlen(tmp));
	if (tmp1)
		free(tmp1);
	free(tmp);
}

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	ft_countchar(char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

static int	min_cd(t_prompt *p, char **str[2], char **aux)
{
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	if (ft_matrixlen(str[0]) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	*aux = ft_getenv("HOME", p->env, 4);
	if (!*aux)
		*aux = ft_strdup("");
	str[1] = ft_update_matrix(NULL, *aux);
	free(*aux);
	return (0);
}

int	ft_cd(t_prompt *p)
{
	char	**str[2];
	char	*aux;

	g_status = 0;
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	if (min_cd(p, str, &aux))
		return (1);
	cd_error(str);
	if (!g_status)
		p->env = ft_setenv("OLDPWD", str[1][1], p->env, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_update_matrix(str[1], aux);
	free(aux);
	p->env = ft_setenv("PWD", str[1][2], p->env, 3);
	ft_free_matrix(&str[1]);
	return (g_status);
}
