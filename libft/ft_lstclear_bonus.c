/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:34:40 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:38:15 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
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
