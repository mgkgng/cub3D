/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/06 00:30:36 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	terminate_parse(char *mapstr, char **map, char *set)
{
	free(mapstr);
	free(map);
	if (set)
		free(set);
	return (0);
}

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
	int	i;
	int	j;
	int	map_width;
	char	*set;

	map_width = ft_strlen(map[0]);
	i = -1;
	while (map[++i])
		if (ft_strlen(map[i]) != map_width)
			return (terminate_parse(mapstr, map, NULL));
	set = ft_strdup(" 10NSWE");
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!ft_strchr(set, map[i][j]))
				return (terminate_parse(mapstr, map, set));
	}
	return (1);
}

t_map	get_map(int fd)
{
	t_map	map;
	char	*line;
	char	*mapstr;

	line = get_next_line(fd);
	mapstr = NULL;
	while (line)
	{
		mapstr = ft_strcat(mapstr, line);
		free(line);
		line = get_next_line(fd);
	}
	map.map = ft_split(mapstr, '\n');
	if (!check_fileformat(mapstr, map.map))
		error(4);
	map.width = ft_strlen(map[0]);
	map.height = 0;
	while (map[map.height])
		map.hegiht++;
	return (map);
}

t_point	*get_lines(char **maps);
{
	int	i;
	int	j;
	int	line_index;
	
	while (map[i])	
	
}

t_game	parse(char *file)
{
	int		fd;
	t_map	map;

	if (!check_filename)
		error(2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(3);
	map = get_map(fd);
	map.lines = get_lines(map.map);
	
	// ... now how to parse? how kind of categories of information?
	close(fd);
}