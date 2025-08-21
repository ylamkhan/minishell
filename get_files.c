/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:54 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 22:08:02 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		mini_perror(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_perror(NPERM, path, 1);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror(NPERM, path, 1);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_mini	*ft_infile2(t_mini *node, char **args, int *i, t_prompt *p)
{
	char	*aux[2];
	char	*error;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->infile = get_here_doc(str, aux, p);
	}
	if (!args[*i] || node->infile == -1)
	{
		if (node->infile != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
	}
	return (node);
}

t_mini	*ft_infile1(t_mini *t, char **args, int *i)
{
	char	*error;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[(*i)])
		t->infile = get_fd(t->infile, args[*i], flags);
	if (!args[*i] || t->infile == -1)
	{
		if (t->infile != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (t);
}

t_mini	*ft_outfile1(t_mini *t, char **args, int *i)
{
	char	*error;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[(*i)])
		t->outfile = get_fd(t->outfile, args[*i], flags);
	if (!args[*i] || t->outfile == -1)
	{
		if (t->outfile != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (t);
}

t_mini	*ft_outfile2(t_mini *t, char **args, int *i)
{
	char	*error;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	error = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
	if (args[++(*i)])
		t->outfile = get_fd(t->outfile, args[*i], flags);
	if (!args[*i] || t->outfile == -1)
	{
		if (t->outfile != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (t);
}
