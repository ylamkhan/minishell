/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:25:23 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/06 20:14:39 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*(s1 + i) != '\0' || *(s2 + i) != '\0')
	{
		if (*(s1 + i) > *(s2 + i))
			return (1);
		else if (*(s1 + i) < *(s2 + i))
			return (-1);
		else
			i++;
	}
	return (0);
}

int	check_arg(char *arg)
{
	int	i;

	if (arg[0] == '\0' || arg[0] == '=' || (arg[0] >= '0' && arg[0] <= '9'))
		return (0);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && (ft_isalnum(arg[i])
			|| arg[i] == '_'))
		i++;
	if (arg[i] == '+' && arg[i + 1] == '=')
	{
		i++;
	}
	if (arg[i] == '\0' || arg[i] == '=')
		return (1);
	else
		return (0);
}
