/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:04:43 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 23:01:14 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*find_cmd(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

DIR	*ft_check_cmd(t_prompt *p, t_list *cmd, char ***s, char *path)
{
	t_mini	*t;
	DIR		*dir;

	dir = NULL;
	t = cmd->content;
	if (t && t->full_cmd)
		dir = opendir(*t->full_cmd);
	if (t && t->full_cmd && ft_strchr(*t->full_cmd, '/') && !dir)
	{
		*s = ft_split(*t->full_cmd, '/');
		t->full_path = ft_strdup(*t->full_cmd);
		free(t->full_cmd[0]);
		t->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1]);
	}
	else if (!is_builtin(t) && t && t->full_cmd && !dir)
	{
		path = ft_getenv("PATH", p->env, 4);
		*s = ft_split(path, ':');
		free(path);
		t->full_path = find_cmd(*s, *t->full_cmd, t->full_path);
		if (!t->full_path || !t->full_cmd[0] || !t->full_cmd[0][0])
			mini_perror(NCMD, *t->full_cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_prompt *p, t_list *cmd, char **s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = ft_check_cmd(p, cmd, &s, path);
	if (!is_builtin(n) && n && n->full_cmd && dir)
		mini_perror(IS_DIR, *n->full_cmd, 126);
	else if (!is_builtin(n) && n && n->full_path && access(n->full_path,
			F_OK) == -1)
		mini_perror(NDIR, n->full_path, 127);
	else if (!is_builtin(n) && n && n->full_path && access(n->full_path,
			X_OK) == -1)
		mini_perror(NPERM, n->full_path, 1);
	if (dir)
		closedir(dir);
	ft_free_matrix(&s);
}

void	*run_cmd(t_prompt *p, t_list *cmds, int *is_exit)
{
	int	fd[2];

	*is_exit = 0;
	get_cmd(p, cmds, NULL, NULL);
	if (pipe(fd) == -1)
		return (mini_perror(PIPERR, NULL, 1));
	if (!check_to_fork(p, cmds, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmds->next && !((t_mini *)cmds->next->content)->infile)
		((t_mini *)cmds->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_mini *)cmds->content)->infile > 2)
		close(((t_mini *)cmds->content)->infile);
	if (((t_mini *)cmds->content)->outfile > 2)
		close(((t_mini *)cmds->content)->outfile);
	return (NULL);
}
