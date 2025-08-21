/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:14:26 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/06 18:32:48 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_count_words(char *input, char *set, int i[2])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (input && i[0] < (int)ft_strlen(input))
	{
		if (!ft_strrchr(set, input[i[0]]))
		{
			i[1]++;
			while ((!ft_strrchr(set, input[i[0]]) || q[0]) && input[i[0]])
			{
				if (!q[1] && (input[i[0]] == '\"' || input[i[0]] == '\''))
					q[1] = input[i[0]];
				q[0] = (q[0] + (input[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **split_tab_esp, char *input, char *set,
		int i[3])
{
	int	s_len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(input);
	while (input[i[0]])
	{
		while (ft_strchr(set, input[i[0]]) && input[i[0]])
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, input[i[0]]) || q[0] || q[1]) && input[i[0]])
		{
			q[0] = (q[0] + (!q[1] && input[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && input[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			split_tab_esp[i[2]++] = "\0";
		else
			split_tab_esp[i[2]++] = ft_substr(input, i[1], i[0] - i[1]);
	}
	return (split_tab_esp);
}

char	**ft_split_tab_esp(char *input, char *set)
{
	char	**split_tab_esp;
	int		nb_words;
	int		i[3];
	int		count[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	count[0] = 0;
	count[1] = 0;
	if (!input)
		return (NULL);
	nb_words = ft_count_words(input, set, count);
	if (nb_words == -1)
		return (NULL);
	split_tab_esp = malloc((nb_words + 1) * sizeof(char *));
	if (split_tab_esp == NULL)
		return (NULL);
	split_tab_esp = ft_fill_array(split_tab_esp, input, set, i);
	split_tab_esp[nb_words] = NULL;
	return (split_tab_esp);
}

char	**ft_split_tab_esp1(char *input, char *set)
{
	char	**split_tab_esp;
	int		nb_words;
	int		i[3];
	int		count[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	count[0] = 0;
	count[1] = 0;
	if (!input)
		return (NULL);
	nb_words = ft_count_words(input, set, count);
	if (nb_words == -1)
		return (NULL);
	split_tab_esp = malloc((nb_words + 1) * sizeof(char *));
	if (split_tab_esp == NULL)
		return (NULL);
	split_tab_esp = ft_fill_array(split_tab_esp, input, set, i);
	split_tab_esp[nb_words] = NULL;
	free(input);
	return (split_tab_esp);
}
