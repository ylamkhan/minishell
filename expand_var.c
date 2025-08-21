/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:55:56 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/06 04:08:31 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_substr_var(char *str, int i, t_prompt *p)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	aux = ft_substr(str, 0, i - 1);
	var = ft_getenv(&str[i], p->env, ft_strchars_i(&str[i], "\"\'$|>< "));
	if (!var && str[i] == '$')
		var = ft_itoa(p->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && ((ft_strchars_i(&str[i
							+ 1], "/~%^{}:; ") && !quotes[1])
				|| (ft_strchars_i(&str[i + 1], "/~%^{}:;\" ") && quotes[1])))
			return (expand_vars(get_substr_var(str, ++i, prompt), -1, quotes,
					prompt));
	}
	return (str);
}

int	check_path(char *s)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	if (ft_count_words(s, " \t", i) != 1)
		return (1);
	return (0);
}

int	ambigous(char **s)
{
	int	i;

	i = 0;
	while (i < ft_matrixlen(s))
	{
		if (ft_matrixlen(s) > 1 && check_path(s[i]) && (s[i - 1][0] == '>'
			|| s[i - 1][0] == '<'))
			return (1);
		i++;
	}
	return (0);
}

char	**split_all(char **args, t_prompt *prompt, int *am)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, ft_getenv("HOME",
					prompt->env, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		funcfree(subsplit);
	}
	if (ambigous(args))
	{
		*am = 1;
		printf("Minishell: ambiguous redirect\n");
		return (funcfree(args), NULL);
	}
	return (args);
}
