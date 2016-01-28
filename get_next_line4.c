/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <vbraeke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 16:06:11 by vbraeke           #+#    #+#             */
/*   Updated: 2016/01/28 19:32:24 by vbraeke          ###   ########.fr       */
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

int		check_rest_return(char **rest, char *buf)
{

	if (*rest)
		*rest = ft_strjoin(*rest, buf);
	else
		*rest = ft_strdup(buf);
	if (ft_strchr(*rest, '\n'))
		return (1);
	return (0);
}

int		check_my_line(char *rest, int n)
{
	int		i;

	i = -1;
	while(++i < n)
	{
		if (rest[i] == '\n')
			return(i);
	}
	return (-2);
}

int		return_line(char **rest, char **line)
{
	int		i;
	int		n;

	n = ft_strlen(*rest);
	i = check_my_line(*rest, n);
	
	if (!*rest)
		return (0);
	if (i < 0)
	{
		*line = ft_strdup(*rest);
		printf("yo%s\n", *line);
		ft_strdel(rest);
	}
	else
	{
		if (i >= 0)
		{
			*line = ft_strnjoin(*line, *rest, i);
		}
		else
			free(*line); line = NULL;
		*rest = ft_strdup(ft_strchr(*rest, '\n'));
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE + 1];
	static char	*rest;
	int ret;
	int	retour;

	if (!line || BUFF_SIZE < 1 || fd < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		retour = check_rest_return(&rest, buf);
		if (retour < 1)
			return(-1);
	}
	retour = return_line(&rest, line);
	printf("po\n");
	return (retour);
}

int		main(int argc, char **argv)
{
	char *line;
	int fd;
	int ret;

	line = ft_strnew(BUFF_SIZE);
	if (argc == 2)
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			return (0);
	}
	
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line = %s\n", line);
	}
	
	close(fd);
	return (0);
}