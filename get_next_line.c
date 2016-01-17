/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 13:42:27 by vbraeke           #+#    #+#             */
/*   Updated: 2016/01/17 19:43:37 by vbraeke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_realloc(char *buf)
{
	char *buf2;
	if (buff == 0)
	{
		if ((buf2 = malloc(sizeof(char) * (BUFF_SIZE + 1))) == 0)
			return (NULL);
	}
	else 
	{
		if ((buf2 = malloc(sizeof(char) * ft_strlen(buff) + BUFF_SIZE + 1)) == 0)
			return (NULL);
		ft_strcpy(buf2, buff);
		free(buff);
	}
	return (buf2);
}

int		get_next_line(int const fd, char **line)
{
	char		*str;
	static char	buff[BUFF_SIZE + 1];
	int			ret;
	static char	*save;

	j = 0;
	if ((str = malloc(sizeof(char) * (BUF_SIZE + 1))) == NULL)
		    return (NULL);
	str[0] = '\0';
	while (str)
	{
		if (buff[i] == '\0')
			str = ft_realloc(str);
		if (!(fd  = open(fd, O_RDONLY)) || fd < 1)
			return (-1);
		if (!(ret = read(fd, line, BUFFER)) || ret < 1)
			return (-1);
		close(fd);
		return (1);
	}
}
