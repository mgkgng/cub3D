/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/04 21:19:43 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (!ft_strcmp(file, ".cub"))
		return (1);
	// there would be some more tricky cases
	return (0);
}

int	check_fileformat(char *mapstr, char **map)
{
	int	e;
	int	i;
	int	map_width;

	e = 0;
	map_width = ft_strlen(map[0]);
	i = -1;
	while (!map[i])
		if (ft_strlen(map[i]) != map_width)
			e = 1;
	// should check what kind of errors there can be.
	if (e)
	{
		free(mapstr);
		free(map);
		return (0);
	}
	return (1);
}

char	**get_map(int fd)
{
	char	*line;
	char	*mapstr;
	char	**map;

	line = get_next_line(fd);
	mapstr = NULL;
	while (line)
	{
		mapstr = ft_strcat(mapstr, line);
		free(line);
		line = get_next_line(fd);
	}
	map = ft_split(mapstr, '\n');
	if (!check_fileformat(mapstr, map))
		error(4);
	return (map);
	
}

t_game	parse(char *file)
{
	int		fd;
	char	**map;

	if (!check_filename)
		error(2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(3);
	map = get_map(fd);
	
	// ... now how to parse? how kind of categories of information?
	close(fd);
}