/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 13:42:27 by vbraeke           #+#    #+#             */
/*   Updated: 2016/01/18 15:55:53 by vbraeke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_line(char *buf)
{
	int		i;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	get_my_line(*buf)
{

}

char	*ft_realloc(char *buf)
{
	char *buf2;
	if (buf == 0)
	{
		if ((buf2 = malloc(sizeof(char) * (BUFF_SIZE + 1))) == 0)
			return (NULL);
	}
	else 
	{
		if ((buf2 = malloc(sizeof(char) * ft_strlen(buf) + BUFF_SIZE + 1)) == 0)
			return (NULL);
		ft_strcpy(buf2, buf);
		free(buf);
	}
	return (buf2);
}

int		get_next_line(int const fd, char **line)
{
	char		*str;
	static char	buf[BUFF_SIZE + 1];
	int			ret;
	static char	*save;
	int			k;

	if (*line != NULL)
	{
		while (read(fd, buf, BUFF_SIZE))
		{
			k = checkline(buf);
			save = ft_realloc(buf);
		}
	}
