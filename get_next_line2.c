/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:18:09 by vbraeke           #+#    #+#             */
/*   Updated: 2016/01/25 16:18:13 by vbraeke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_bzero(res, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strncat(res, s2, n);
	return (res);
}


void	check_my_line(int fd, char **rest, char **line)
{
	int i = -1;
	while (++i < ft_strlen(*rest))
	{
		if ((*rest)[i] && (*rest)[i] == '\n')
		{
			*line = ft_strsub(*rest, 0, i);
			printf("LINE%s\n", *line);
			if (i + 1 < ft_strlen(*rest))
				*rest = ft_strsub(*rest, i + 1, ft_strlen(*rest));
			return ;
		}
	}
	printf("LINE%s\n", *line);
	*line = ft_strdup(*rest);
	ft_strdel(rest);
	get_next_line(fd, line);
}

int		get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*rest;
	static int		i;
	char		*buf2;
	int 		ret;

	rest = NULL;
	if (fd < 0 || BUFF_SIZE < 1|| !line)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		check_my_line(fd, &rest, line);
		printf("I = %d\n", i);
		if (i == BUFF_SIZE)
		{
			buf2 = ft_strsub(buf, 0, i);
			printf("buf2%s\n", buf2);
		}
		if (i != BUFF_SIZE)
		{
			*line = ft_strnjoin(buf2, buf, i);
			rest = ft_strsub(buf, i, BUFF_SIZE);
			printf("rest%s\n", rest);
			printf("line%s\n", *line);
		}
		if (ret < BUFF_SIZE)
		{
			printf("File end\n");
			return (0);
		}	
	}
	return (1);
}

int		main(int argc, char **argv)
{
	char *line;
	int fd;
	//int i = 1;
	int ret;

	line = ft_strnew(BUFF_SIZE);
	if (argc == 2)
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			return (0);
	}
	else
		fd = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		//printf("line = %s\n", line);
		//printf("ret = %d\n", ret);
	}
	//printf("NEXT_LINE: %s\n", line);
	close(fd);
	return (0);
}