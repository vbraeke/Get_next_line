/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:58:09 by vbraeke           #+#    #+#             */
/*   Updated: 2016/02/03 00:58:12 by vbraeke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_realloc_rest(char **rest, size_t i)
{
	char *tmp;
	tmp = ft_strdup(*rest + i + 1);
	ft_strdel(rest);
	*rest = ft_strdup(tmp);
}

void	ft_realloc_line(char **line, char **rest, int i)
{
	char *tmp;

	tmp = ft_strsub(*rest, 0, i);
	*line = ft_strdup(tmp);
	free(tmp);
}

void	ft_save(char *buf, char **rest)
{
	char *tmp;

	if (*rest == NULL)
		*rest = ft_strdup(buf);
	else
	{
		tmp = ft_strdup(*rest);
		ft_strdel(rest);
		*rest = ft_strjoin(tmp, buf);
	}
}

int		get_next_line(int const fd, char **line)
{
	int ret;
	int i;
	char buf[BUFF_SIZE + 1];
	static char *rest;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		ft_save(buf, &rest);
	}
	if (rest[0] == '\0')
		return (0);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	ft_realloc_line(line, &rest, i);
	ft_realloc_rest(&rest, i);
	if (rest[i] == '\n' && ((rest[i + 1]) == '\0'))
		return(0);
	return (1);
}

/*int		main(int argc, char **argv)
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
}*/
