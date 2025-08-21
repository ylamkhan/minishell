/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 03:40:33 by zsaoud            #+#    #+#             */
/*   Updated: 2023/08/06 06:12:25 by ylamkhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ret_line(char *str);
size_t	ft_strlen1(char *str);
int		end_line(char *str);
char	*ft_strdup1(char *s1);
char	*ft_strjoin1(char *s1, char *s2);
char	*remplire_line(char *reserve);
char	*remplire(int fd, char *reserve);
char	*ft_update(char *reserve);
#endif