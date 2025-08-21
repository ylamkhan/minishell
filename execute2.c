/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:56:53 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/03 17:58:32 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_putmatrix_fd(char **m, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (!strcmp(env_get_value(m[i], m), "zinebismarriedtoyoussef"))
			i++;
		else
		{
			if (nl)
				count += ft_putendl_fd(m[i], fd);
			else
				count += ft_putstr_fd(m[i], fd);
			i++;
		}
	}
	return (count);
}
