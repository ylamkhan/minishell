/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:40:46 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/01 15:41:41 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int				a;
	unsigned int	i;
	char			*str;
	char			*s;

	str = (char *)haystack;
	if (needle[0] == '\0')
		return (str);
	if (len == 0 && haystack == NULL)
		return (NULL);
	s = (char *)needle;
	a = ft_strlen(s);
	i = 0;
	while (str[i] && i < len)
	{
		if (a + i > len)
			return (NULL);
		if (s[0] == str[i] && ft_strncmp(str + i, s, a) == 0)
			return (str + i);
		i++;
	}
	return (NULL);
}
