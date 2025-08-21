/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:09:07 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/06 22:41:52 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_content(void *content)
{
	t_mini	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

void	execute(int *is_exit, int *i, t_prompt *p)
{
	int	youssef;

	youssef = 1;
	*i = ft_lstsize(p->cmds);
	g_status = built(p, p->cmds, is_exit, &youssef);
	while ((*i)-- > 0)
		waitpid(-1, &g_status, 0);
	if (!youssef)
	{
		if (g_status == 13)
			g_status = 127;
		else if (g_status == 126)
			g_status = 126;
		else if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
	}
	if (g_status == 129)
		g_status = 1;
}

static void	*parse_args(char **args, t_prompt *p, int *am)
{
	int		is_exit;
	int		i;
	char	*t;
	char	**s;
	char	**tmp;

	*am = 0;
	is_exit = 0;
	tmp = split_all(args, p, am);
	t = join_all(tmp);
	funcfree(tmp);
	s = NULL;
	if (t)
		s = ft_split_tab_esp1(t, " \t");
	if (s)
		p->cmds = fill_nodes(s, -1, p);
	if (!p->cmds)
		return (p);
	execute(&is_exit, &i, p);
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

int	check(char *input)
{
	if (!input)
	{
		printf("exit\n");
		free(input);
		exit(g_status);
	}
	if (max_her_doc(input))
	{
		free(input);
		exit(2);
	}
	if (input[0])
		add_history(input);
	if (syntax_error(input) || backslach_point(input))
		return (1);
	return (0);
}

void	*check_args(char *input, t_prompt *p)
{
	char	**split_tab_esp;
	int		am;

	if (check(input))
		return (free(input), "");
	split_tab_esp = ft_split_tab_esp(input, " \t");
	free(input);
	if (split_tab_esp[0] == 0)
		return (funcfree(split_tab_esp), "");
	if (!split_tab_esp)
		return ("");
	p = parse_args(split_tab_esp, p, &am);
	if (!p && am)
		return ("");
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
