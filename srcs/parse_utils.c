/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:03:47 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/25 17:02:58 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**get_lines(int fd)
{
	char	*line;
	char	*r;
	char	**res;

	r = NULL;
	line = get_next_line(fd);
	while (line)
	{
		r = ft_strcat(r, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	res = ft_split(r, '\n');
	free(r);
	return (res);
}

int	get_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		end_program(filename, 1);
	}
	return (fd);
}

int	ft_tablen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
