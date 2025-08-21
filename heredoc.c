/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:06:04 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 22:00:20 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	max_her_doc(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			count++;
			i++;
		}
		i++;
	}
	if (count > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		g_status = 2;
		return (1);
	}
	return (0);
}

char	*get_str(char *str[2], size_t len, char *s1[2], t_prompt *p)
{
	char	*temp[2];
	int		q[2];

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], s1[0], len)
			|| ft_strlen(s1[0]) != len))
	{
		(signal(SIGINT, handle_sigint), signal(SIGQUIT, SIG_IGN));
		temp[0] = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp[0]);
		if (str[0])
			free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", s1[1], s1[0]);
			break ;
		}
		temp[0] = str[0];
		temp[1] = expand_vars(temp[0], -1, q, p);
		str[0] = ft_strjoin(temp[1], "\n");
		free(temp[1]);
		len = ft_strlen(str[0]) - 1;
	}
	return (free(str[0]), str[1]);
}

int	get_here_doc(char *str[2], char *a[2], t_prompt *p)
{
	int	fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = get_str(str, 0, a, p);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_status == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
