/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 13:42:27 by vbraeke           #+#    #+#             */
/*   Updated: 2016/01/19 17:51:37 by vbraeke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(const char *s1, const char *s2, size_t n)
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

int		check_my_line(char *buf, char **line, char **rest)
{
	size_t		i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			*line = ft_strnjoin(*rest, buf, i);
			printf("line = %s\n", *line);
			*rest = ft_strnew(BUFF_SIZE);
			printf("rest = %s\n", *line);
			return (0);	
		}
		i++;
	}
	*rest = ft_strjoin(*line, ft_strsub(buf, 0 , BUFF_SIZE));
	//printf("check_line%s\n", *line);
	//printf("rest = %s\n", *rest);
	return (1);
}

void	read_my_file(char **rest, int const fd, char *buf, char **line)
{
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		check_my_line(buf, line, rest);
		//printf("myline%s\n", *line);
		//printf("buf =%s\n", buf);
		//printf("ret =%d\n", ret);
		if (ret < BUFF_SIZE)
			printf("FINISH\n");
	}
}

int		get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE];
	static char	*rest;
	int			len;

	rest = NULL;
	if (fd < 0 || BUFF_SIZE < 1|| !line)
		return (-1);
	read_my_file(&rest, fd, buf, line);
	return (0);
	if (check_my_line(buf, line, &rest) == 0)
		return (1);
}

int		main(int argc, char **argv)
{
	char *line;
	int fd;
	//int i = 1;
	int ret;

	line = ft_strnew(0);
	if (argc == 2)
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			return (0);
	}
	else
		fd = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line = %s\n", line);
		//printf("ret = %d\n", ret);
	}
	//printf("NEXT_LINE: %s\n", line);
	close(fd);
	return (0);
}