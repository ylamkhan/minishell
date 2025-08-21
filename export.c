/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 23:02:42 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	print_vars(char **env);

void	split_sort1(char **split)
{
	char	*tmp;
	int		i_strs;
	int		i;
	int		j;

	i_strs = ft_matrixlen(split);
	i = 0;
	while (i < i_strs - 1)
	{
		j = 0;
		while (j < (i_strs - 1 - i))
		{
			if (ft_strncmp(split[j], split[j + 1], ft_strlen(split[j]) + 1) > 0)
			{
				tmp = split[j];
				split[j] = split[j + 1];
				split[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_vars(char **env)
{
	char	**env_copy;
	int		l_var_name;
	int		i;

	if (env == NULL || *env == NULL)
		return ;
	env_copy = malloc((ft_matrixlen(env) + 1) * sizeof(char *));
	env_copy = ft_memcpy(env_copy, env, (ft_matrixlen(env) + 1)
			* sizeof(char *));
	split_sort1(env_copy);
	i = 0;
	while (env_copy[i])
	{
		if (!ft_strcmp(env_get_value(env_copy[i], env),
				"zinebismarriedtoyoussef"))
			printf("%s\n", ft_split(env_copy[i], '=')[0]);
		else
		{
			l_var_name = ft_strchr(env_copy[i], '=') - env_copy[i];
			printf("%.*s", l_var_name + 1, env_copy[i]);
			printf("\"%s\"\n", env_get_value(env_copy[i], env));
		}
		i++;
	}
	free(env_copy);
}

void	add_var(t_prompt **p, char *v)
{
	char	**a;
	char	*tmp;
	int		i;

	a = ft_split(v, '=');
	tmp = NULL;
	if (!ft_strchr(a[0], '+'))
		(*p)->env = ft_setenv(a[0], a[1], (*p)->env, ft_strlen(a[0]));
	else
	{
		i = -1;
		tmp = malloc(ft_strlen(a[0]) - 1);
		if (tmp == NULL)
			return ;
		while (++i < (int)ft_strlen(a[0]) - 1)
			tmp[i] = a[0][i];
		tmp[i] = '\0';
		fun3(p, tmp, a[1]);
	}
	funcfree(a);
}

void	add_null(t_prompt *p, char *var)
{
	char	*msg;
	char	*g;

	msg = "zinebismarriedtoyoussef";
	g = ft_getenv(var, p->env, ft_strlen(var));
	if (!g)
		p->env = ft_setenv(var, msg, p->env, ft_strlen(var));
	free(g);
}

int	ft_export(t_prompt *p)
{
	t_mini	*cmd;
	int		i;

	g_status = 0;
	cmd = (t_mini *)(p->cmds->content);
	if (cmd->full_cmd && !cmd->full_cmd[1])
		print_vars(p->env);
	i = 0;
	while (ft_matrixlen(cmd->full_cmd) > 1 && cmd->full_cmd[i + 1])
	{
		i++;
		if (!check_arg(cmd->full_cmd[i]))
			mini_perror1(EXPORT, NULL, 1);
		else if (!ft_strchr(cmd->full_cmd[i], '='))
			add_null(p, cmd->full_cmd[i]);
		else if (ft_strchr(cmd->full_cmd[i], '='))
			add_var(&p, cmd->full_cmd[i]);
	}
	return (g_status);
}
