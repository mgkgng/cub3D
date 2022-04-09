/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/09 15:09:34 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// parsing should be done again.

//** an idea for parsing -> after having figured out informations about the character,
//** i'm going to make a map composed by BOOLIAN VALUES. (Wall == TRUE. Else == FALSE)

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



static void	put_player_info(t_map *map, int *pos, char dir, char **set_dir)
{
	map->pos.x = pos[0];
	map->pos.y = pos[1];
	if (dir == 'N')
		map->theta = 270;
	else if (dir == 'S')
		map->theta = 90;
	else if (dir == 'W')
		map->theta = 180;
	else
		map->theta = 0;
	free(*set_dir);
	*set_dir = NULL;
}

static void	put_info(t_map *map, char **map_data)
{
	//** what to do
	//** 1. map_width (maximum)
	//** 2. map_height
	//** 3. position of the character
	//** 4. and where it is heading to

	int	max_width;
	int	i;
	int	j;
	char	*set_dir;
	
	i = -1;
	max_width = 0;
	set_dir = ft_strdup("NSWE");
	while (map_data[++i])
	{
		j = -1;
		while (map_data[i][++j])
			if (set_dir && ft_strchr(set_dir, map_data[i][j]))
				put_player_info(map, (int [2]) {i, j}, map_data[i][j], &set_dir);
		if (j > max_width)
			max_width = j;
	}
	map->height = i;
	map->width = max_width;
}

static bool	**get_boolmap(char **charmap, int map_width, int map_height)
{
	bool	**boolmap;
	int		i;
	int		j;

	boolmap = ft_calloc(map_width * map_height, sizeof(bool));
	i = -1;
	while (charmap[++i])
	{
		j = -1;
		while (charmap[i][++j])
			if (!(charmap[i][j] == ' ' || charmap[i][j] == '1'))
				boolmap[i][j] = true;
	}
	free(charmap);
	return (boolmap);
}

t_map	get_map(int fd)
{
	t_map	map;
	char	*line;
	char	*mapstr;
	char	**map_data;

	line = get_next_line(fd);
	mapstr = NULL;
	while (line)
	{
		mapstr = ft_strcat(mapstr, line);
		free(line);
		line = get_next_line(fd);
	}
	map_data = ft_split(mapstr, '\n');\
	if (!check_fileformat(mapstr, map_data))
		error(4);
	put_info(&map, map_data);
	map.map2d = get_boolmap(map_data, map.width, map.height);
	return (map);
}

/*static void	put_player_dir(t_map *map, char dir)
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
}*/



t_game	parse(char *file)
{
	int		fd;
	t_game	game;

	if (!check_filename(file))
		error(2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(3);
	game.map = get_map(fd);
	
	// ... now how to parse? how kind of categories of information?
	close(fd);
	return (game);
}

// only thing to think about is whether it's more efficient to put the character's coordinates as
// (0, 0) or something else. (then it must be the first element of the map should have (0,0) as its coordinates
// and character's position should be changed as soon as it moves.)