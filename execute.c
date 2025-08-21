/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:04:34 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 23:00:46 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_child(t_prompt *p, t_mini *t, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(t) && t->full_cmd)
		execve(t->full_path, t->full_cmd, p->env);
	else if (t->full_cmd && !ft_strncmp(*t->full_cmd, "pwd", l) && l == 3)
		g_status = ft_pwd();
	else if (is_builtin(t) && t->full_cmd && !ft_strncmp(*t->full_cmd, "echo",
			l) && l == 4)
		g_status = ft_echo(cmd);
	else if (is_builtin(t) && t->full_cmd && !ft_strncmp(*t->full_cmd, "export",
			l) && l == 6)
		g_status = ft_export(p);
	else if (is_builtin(t) && t->full_cmd && !ft_strncmp(*t->full_cmd, "env", l)
		&& l == 3)
	{
		ft_putmatrix_fd(p->env, 1, 1);
		g_status = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (mini_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->full_cmd)
		l = ft_strlen(*n->full_cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	ft_child(prompt, n, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void	exec_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(prompt, cmd, fd);
}

void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*t;
	DIR		*dir;

	t = cmd->content;
	dir = NULL;
	if (t->full_cmd)
		dir = opendir(*t->full_cmd);
	if (t->infile == -1 || t->outfile == -1)
		return (NULL);
	if ((t->full_path && access(t->full_path, X_OK) == 0) || is_builtin(t))
		exec_fork(prompt, cmd, fd);
	else if (!is_builtin(t) && ((t->full_path && !access(t->full_path, F_OK))
			|| dir))
		g_status = 126;
	else if (!is_builtin(t) && t->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
