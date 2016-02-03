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

int		ft_check(char *rest)
{
	int		i;

	i = -1;
	while(++i && rest[i] != '\0')
	{
		if (rest[i] == '\n')
			return(i);
	}
	return (-1);
}

int		ft_read(int const fd, char **rest, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (*rest)
		{
			*rest = ft_strjoin(*rest, buf);
		}
		else
		{
			*rest = ft_strdup(buf);
		}
		if (ft_check(*rest) != -1)
		{
			i = ft_get(&rest, line);
			return (1);
		}
	}
	return (0);
}

int		ft_get(char **rest, char **line)
{
	char	*tmp;
	int		i;

	if (*rest)
	{
		i = ft_check(*rest);
		if (i == -1)
		{
			return (0);
		}
		if (i == 0)
		{
			
		}
		if (i != -1)
		{
			*line = ft_strsub(*rest, 0, i - 1);
			tmp = ft_strsub(*rest, i + 1, ((i + 1) - (i - 1)));
			ft_strdel(rest);
			*rest = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	int				i;
	static char 	*rest;

	if (!*line || !line || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (rest)
	{
		i = ft_check(rest);
		if (i != -1)
		{
			i = 0;
			i = ft_get(&rest, line);
			return (i);
		}
	}
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
