/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbraeke <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:58:09 by vbraeke           #+#    #+#             */
/*   Updated: 2016/02/07 17:29:13 by vbraeke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_dup_rest(char **rest, size_t i)
{
	char *tmp;

	if (i == ft_strlen(*rest))
	{
		ft_strdel(rest);
		return (1);
	}
	tmp = ft_strdup(*rest + i + 1);
	ft_strdel(rest);
	*rest = ft_strdup(tmp);
	return (1);
}

void	ft_dup_line(char **line, char **rest, size_t i)
{
	char *tmp;

	tmp = ft_strsub(*rest, 0, i);
	*line = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void	ft_join(char *buf, char **rest)
{
	char *tmp;

	if (*rest == NULL)
		*rest = ft_strdup(buf);
	else
	{
		tmp = ft_strdup(*rest);
		ft_strdel(rest);
		*rest = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
	}
}

int		get_next_line(int const fd, char **line)
{
	int			ret;
	size_t		i;
	char		buf[BUFF_SIZE + 1];
	static char *rest;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		ft_join(buf, &rest);
	}
	if ((rest == NULL && ret == 0) || (rest[0] == '\0'))
		return (0);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	ft_dup_line(line, &rest, i);
	ft_dup_rest(&rest, i);
	return (1);
}
