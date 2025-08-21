/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:34:48 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/05 03:46:43 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!(*lst))
		return ;
	else
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}
