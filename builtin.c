/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:03:51 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 04:00:58 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	built(t_prompt *p, t_list *cmds, int *exitt, int *youssef)
{
	char	**a;

	while (cmds)
	{
		a = ((t_mini *)cmds->content)->full_cmd;
		if (a && !strncmp(*a, "exit", ft_strlen(*a)) && ft_strlen(*a) == 4)
			g_status = ft_exit(cmds, exitt);
		else if (!cmds->next && a && !strncmp(*a, "cd", ft_strlen(*a))
			&& ft_strlen(*a) == 2 && ((t_mini *)cmds->content)->infile == 0)
			g_status = ft_cd(p);
		else if (!cmds->next && a && !ft_strncmp(*a, "export", ft_strlen(*a))
			&& ft_strlen(*a) == 6 && ((t_mini *)cmds->content)->outfile == 1)
			g_status = ft_export(p);
		else if (!cmds->next && a && !strncmp(*a, "unset", ft_strlen(*a))
			&& ft_strlen(*a) == 5)
			g_status = ft_unset(p);
		else
		{
			(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
			run_cmd(p, cmds, youssef);
		}
		cmds = cmds->next;
	}
	return (g_status);
}

int	is_builtin(t_mini *n)
{
	int	l;

	if (!n->full_cmd)
		return (0);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path
			&& ft_strchr(n->full_path, '/')))
		return (0);
	l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}
