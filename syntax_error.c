/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:07:03 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 22:54:22 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	d_s_quote(char *input, int *i)
{
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (!input[*i])
		{
			mini_perror(QUOTE, NULL, 258);
			return (1);
		}
	}
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'' && input[*i])
			(*i)++;
		if (!input[*i])
		{
			mini_perror(QUOTE, NULL, 258);
			return (1);
		}
	}
	return (0);
}

int	f2(char *tab)
{
	if (ft_strlen(tab) == 2)
	{
		if (tab[0] == tab[1])
		{
			if (tab[0] == '|')
			{
				printf("syntax error near unexpected symbol:\" %s \"\n", tab);
				g_status = 258;
				return (1);
			}
		}
		else
		{
			printf("syntax error near unexpected symbol: \" %s \"\n", tab);
			g_status = 258;
			return (1);
		}
	}
	return (0);
}

int	f1(char *input, int *i, char **tab)
{
	int	count;
	int	j;

	count = *i;
	while (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
		(*i)++;
	(*i)--;
	*tab = malloc(*i - count + 2);
	j = 0;
	while (input[count] && count <= *i)
		(*tab)[j++] = input[count++];
	(*tab)[j] = '\0';
	if (ft_strlen(*tab) >= 3)
	{
		printf("syntax error near unexpected symbol: \" %s \"\n", *tab);
		g_status = 258;
		free(*tab);
		return (1);
	}
	else
	{
		if (f2(*tab))
			return (free(*tab), 1);
	}
	return (free(*tab), 0);
}

int	syntax_error(char *input)
{
	int		i;
	char	*tab;

	tab = NULL;
	i = 0;
	while (input[i])
	{
		if (d_s_quote(input, &i))
			return (1);
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			if (f1(input, &i, &tab))
				return (1);
		}
		i++;
	}
	return (0);
}

int	backslach_point(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (d_s_quote(input, &i))
			return (1);
		if (input[i] == '\\' || input[i] == ';')
		{
			printf("syntax error near unexpected symbol: \" %c \"\n", input[i]);
			g_status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
