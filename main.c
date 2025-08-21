/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:06:16 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 23:03:44 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	ft_getpid(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->env);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

static t_prompt	init_vars(t_prompt p, char *s, char **av)
{
	char	*a;

	s = getcwd(NULL, 0);
	p.env = ft_setenv("PWD", s, p.env, 3);
	free(s);
	s = ft_getenv("SHLVL", p.env, 5);
	if (!s || ft_atoi(s) <= 0)
		a = ft_strdup("1");
	else
		a = ft_itoa(ft_atoi(s) + 1);
	free(s);
	p.env = ft_setenv("SHLVL", a, p.env, 5);
	free(a);
	s = ft_getenv("PATH", p.env, 4);
	if (!s)
		p.env = ft_setenv("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin",
				p.env,
				4);
	free(s);
	s = ft_getenv("_", p.env, 1);
	if (!s)
		p.env = ft_setenv("_", av[0], p.env, 1);
	free(s);
	return (p);
}

t_prompt	init_p(char **av, char **env)
{
	t_prompt	p;
	char		*s;

	s = NULL;
	p.cmds = NULL;
	p.env = ft_dup_matrix(env);
	g_status = 0;
	ft_getpid(&p);
	p = init_vars(p, s, av);
	return (p);
}

int	main(int ac, char **av, char **env)
{
	char		*input[2];
	t_prompt	p;

	(void)ac;
	p = init_p(av, env);
	while (1)
	{
		(signal(SIGINT, handle_sigint), signal(SIGQUIT, SIG_IGN));
		input[1] = ft_getprompt(p);
		if (input[1])
			input[0] = readline(input[1]);
		else
			input[0] = readline("guest@minishell $ ");
		if (input[0] && !input[0][0])
		{
			(free(input[1]), free(input[0]));
			continue ;
		}
		free(input[1]);
		signal(SIGINT, SIG_IGN);
		if (!check_args(input[0], &p))
			break ;
	}
	exit(g_status);
}
