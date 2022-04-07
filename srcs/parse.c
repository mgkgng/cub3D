/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/07 18:54:04 by min-kang         ###   ########.fr       */
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
	if (!ft_strcmp(file + len - 4, ".cub"))
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

	// check n.1 : is there any other character than one of the ones needed to be
	set = ft_strdup(" 10NSWE");
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!ft_strchr(set, map[i][j]))
				return (terminate_parse(mapstr, map, set));
	}
	// check n.2 : is the map is well surrounded by wall?
	// check n.3 : is there only one character?
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
	return (map);
}

static void	put_player_dir(t_map *map, char dir)
{
	if (dir == 'N')
	{
		map->dir.x = 0;
		map->dir.y = -1;
		map->theta = 270;
	}
	else if (dir == 'S')
	{
		map->dir.x = 0;
		map->dir.y = 1;
		map->theta = 90;
	}
	else if (dir == 'W')
	{
		map->dir.x = -1;
		map->dir.y = 0;
		map->theta = 180;
	}
	else
	{
		map->dir.x = 1;
		map->dir.y = 0;
		map->theta = 0;
	}
}

void	put_player_info(t_map *map)
{
	int	i;
	int	j;
	char	**set;

	set = ft_strdup("NSWE");
	i = -1;
	while (map->map2d[++i])
	{
		j = -1;
		while (map->map2d[i][++j])
		{
			if (ft_strchr(set, map[i][j]))
			{
				map->pos.x = i;
				map->pos.y = j;
				put_player_dir(map, map[i][j]);
				free(set);
				return ;
			}
		}
	}
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

// only thing to think about is whether it's more efficient to put the character's coordinates as
// (0, 0) or something else. (then it must be the first element of the map should have (0,0) as its coordinates
// and character's position should be changed as soon as it moves.)