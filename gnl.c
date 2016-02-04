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

	i = 0;
	while(rest[i])
	{
		if (rest[i] == '\n')
			return(i);
		i++;
	}
	return (-1);
}

int		ft_read(int const fd, char **rest, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	int i;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		printf("1\n");
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (*rest)
		{
			i = ft_check(*rest);
			if (i == 0)
			{
				return (1);
			}
			*rest = ft_strjoin(*rest, buf);
		}
		else
		{
			*rest = ft_strdup(buf);
		}
		printf("CPY BUF TO REST = %s\n", *rest);
		if (ft_check(*rest) != -1)
		{
			i = ft_get(rest, line);
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
		if (i == 0)
		{
			*line = ft_strnew(1);
		}
		if (i != -1)
		{
			printf("I = %d\n", i);
			printf("GET=%s\n", *rest);
			*line = ft_strsub(*rest, 0, i);
			printf("GET LINE %s\n", *line);
			tmp = ft_strsub(*rest, i + 1, ft_strlen(*rest) - i);
			ft_strdel(rest);
			*rest = ft_strdup(tmp);
			printf("FiNaL rest%s\n", *rest);
			ft_strdel(&tmp);
			return (1);
		}
	}
	return (0);
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
		if (i == 0)
			return (1);
		if (i != -1)
		{
			i = 0;
			i = ft_get(&rest, line);
			return (i);
		}
	}
	else 
	{
		i = ft_read(fd, &rest, line);
		return (i);
	}
	return (i);
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
