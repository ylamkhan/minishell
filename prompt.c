/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:06:44 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/03 17:49:16 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	update_output(char ***matrix, int fd)
{
	char	**aux;
	char	*temp;
	char	*line;

	aux = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
		aux = ft_update_matrix(aux, temp);
		free(temp);
	}
	ft_free_matrix(matrix);
	*matrix = aux;
}

void	exec_custom(char ***out, char *full, char *args, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**matrix;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		matrix = ft_split(args, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		execve(full, matrix, envp);
		exit(1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(out, fd[READ_END]);
	close(fd[READ_END]);
}

static char	*get_home(t_prompt p)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("° ");
	home = ft_getenv("HOME", p.env, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home) + 1]);
		free(temp);
	}
	free(home);
	home = ft_strjoin(GREEN, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

static char	*get_user(t_prompt p)
{
	char	**user;
	char	*temp;
	char	*temp2;

	user = NULL;
	temp2 = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", p.env);
	if (!user)
		user = ft_update_matrix(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		temp2 = ft_strjoin(NULL, RED);
	if (user[0][0] == 'y')
		temp2 = ft_strjoin(NULL, YELLOW);
	if (user[0][0] == 'z')
		temp2 = ft_strjoin(NULL, PINK);
	temp = ft_strjoin(temp2, *user);
	free(temp2);
	ft_free_matrix(&user);
	return (temp);
}

char	*ft_getprompt(t_prompt p)
{
	char	*temp;
	char	*temp2;
	char	*aux;

	temp = get_user(p);
	temp2 = ft_strjoin(temp, "@minishell");
	free(temp);
	aux = get_home(p);
	temp = ft_strjoin(temp2, aux);
	free(aux);
	free(temp2);
	if (!g_status || g_status == -1)
		temp2 = ft_strjoin(temp, GREEN);
	else
		temp2 = ft_strjoin(temp, RED);
	free(temp);
	temp = ft_strjoin(temp2, "$ ");
	free(temp2);
	temp2 = ft_strjoin(temp, DEFAULT);
	free(temp);
	return (temp2);
}
