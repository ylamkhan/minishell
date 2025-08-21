/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 03:40:24 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 03:40:40 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	int		a_len;
	int		b_len;
	int		i;
	char	*ret;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup1(s2));
	a_len = ft_strlen1(s1);
	b_len = ft_strlen1(s2);
	i = -1;
	ret = (char *)malloc(sizeof(char) * (a_len + b_len + 1));
	if (!ret)
		return (0);
	while (s1[++i])
		ret[i] = s1[i];
	i = -1;
	while (s2[++i])
		ret[a_len + i] = s2[i];
	ret[a_len + i] = '\0';
	free(s1);
	return (ret);
}

char	*ft_update(char *reserve)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	if (!reserve)
		return (NULL);
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i] || !reserve[i + 1])
	{
		free(reserve);
		return (NULL);
	}
	new = malloc(ft_strlen1(reserve) - i);
	if (!new)
		return (NULL);
	j = 0;
	i++;
	while (reserve[i])
		new[j++] = reserve[i++];
	new[j] = '\0';
	free(reserve);
	return (new);
}

char	*remplire(int fd, char *reserve)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (end_line(buffer))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(reserve);
			return (NULL);
		}
		if (!i)
			break ;
		buffer[i] = '\0';
		reserve = ft_strjoin1(reserve, buffer);
	}
	free(buffer);
	return (reserve);
}

char	*remplire_line(char *reserve)
{
	char	*str;
	int		i;

	i = 0;
	if (!reserve)
		return (NULL);
	str = malloc(ret_line(reserve) + 1);
	if (!str)
		return (NULL);
	while (reserve[i] && reserve[i] != '\n')
	{
		str[i] = reserve[i];
		i++;
	}
	if (reserve[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve = remplire(fd, reserve);
	if (!reserve)
		return (NULL);
	line = remplire_line(reserve);
	reserve = ft_update(reserve);
	return (line);
}
