/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:28 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 19:26:04 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_mini	*ft_init(void)
{
	t_mini	*m;

	m = malloc(sizeof(t_mini));
	if (!m)
		return (NULL);
	m->full_cmd = NULL;
	m->full_path = NULL;
	m->infile = STDIN_FILENO;
	m->outfile = STDOUT_FILENO;
	return (m);
}

static t_mini	*get_params(t_mini *node, char **a[2], int *i, t_prompt *p)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = ft_outfile2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = ft_outfile1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] == '<')
			node = ft_infile2(node, a[1], i, p);
		else if (a[0][*i][0] == '<')
			node = ft_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = ft_update_matrix(node->full_cmd, a[1][*i]);
		else
		{
			mini_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

static char	**del_quotes(char **s)
{
	char	**out;
	char	*temp;
	int		i;

	i = -1;
	out = ft_dup_matrix(s);
	while (out && out[++i])
	{
		temp = ft_del(out[i], 0, 0);
		free(out[i]);
		out[i] = temp;
	}
	return (out);
}

static void	*ft_stop(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	g_status = 258;
	return (NULL);
}

t_list	*fill_nodes(char **args, int i, t_prompt *p)
{
	t_list	*cmds[2];
	char	**s[2];

	cmds[0] = NULL;
	s[1] = del_quotes(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(ft_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		s[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, s, &i, p);
		if (i < 0)
			return (ft_stop(cmds[0], args, s[1]));
		if (!args[i])
			break ;
	}
	funcfree(s[1]);
	funcfree(args);
	return (cmds[0]);
}
