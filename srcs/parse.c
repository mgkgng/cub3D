/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/14 22:27:45 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	put_player_info(t_map *map, int *pos, char dir, char **set_dir)
{
	map->pos.x = pos[0];
	map->pos.y = pos[1];
	if (dir == 'N')
		map->theta = 3 * M_PI_2;
	else if (dir == 'S')
		map->theta = M_PI_2;
	else if (dir == 'W')
		map->theta = M_PI;
	else
		map->theta = 0;
	free(*set_dir);
	*set_dir = NULL;
}

static void	put_info(t_map *map, char **map_data, int map_width, int map_height)
{
	int	max_width;
	int	i;
	int	j;
	char	*set_dir;
	
	i = -1;
	max_width = 0;
	set_dir = ft_strdup("NSWE");
	while (++i < map_height)
	{
		j = -1;
		while (++j < map_width)
			if (set_dir && ft_strchr(set_dir, map_data[i][j]))
				put_player_info(map, (int [2]) {i, j}, map_data[i][j], &set_dir);
		if (j > max_width)
			max_width = j;
	}
	map->height = i;
	map->width = max_width;
}

static void put_maps(t_map *map, char **charmap, int map_width, int map_height)
{
	int		i;
	int		j;

	map->map_wall = ft_calloc(map_height, sizeof(char *));
	map->map_move = ft_calloc(map_height, sizeof(bool *));
	i = -1;
	while (++i < map_height)
	{
		map->map_move[i] = ft_calloc(map_width, sizeof(bool));
		map->map_wall[i] = ft_calloc(map_width, sizeof(char));
	}
	i = -1;
	while (++i < map_height)
	{
		j = -1;
		while (++j < map_width)
		{
			if (!charmap[i][j])
				while (j < map_width)
					map->map_wall[i][j] = '1';
			else if (!(charmap[i][j] == ' ' || charmap[i][j] == '1' || charmap[i][j] == 'D'))
				map->map_move[i][j] = true;
			map->map_wall[i][j] = charmap[i][j];
		}
	}
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
	map_data = ft_split(mapstr, '\n');
	is_surrounded(map_data, map.width, map.height);
	if (!check_fileformat(mapstr, map_data, map.width, map.height))
		error(4);
	put_info(&map, map_data, map.width, map.height);
	put_maps(&map, map_data, map.width, map.height);
	return (map);
}

t_draw	put_draw(char **info)
{
	t_draw	draw;
	int		i;
	
	i = -1;
	while (++i < 4)
		draw.nswe[i] = ft_strtrim(info[i] + 2, " \n");
	draw.col_floor = get_color(ft_strtrim(info[4] + 1, " \n"));
	draw.col_ceil = get_color(ft_strtrim(info[5] + 1, " \n"));
	free(info);
	return (draw);
}

t_draw	get_draw(int fd)
{
	char	**info;
	char	*line;
	int		i;

	info = ft_calloc(6, sizeof(char *));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2)
			|| !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			info[i++] = line;
		else
			free(line);
		if (i == 6)
			break; // i should find a way more elegant
		line = get_next_line(fd);
	}
	if (i < 6)
		error(5);
	return (put_draw(info));
}

t_game	parse(char *file)
{
	int		fd;
	t_game	game;

	if (!check_filename(file))
		error(2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(3);
	//game.draw = get_draw(fd);
	game.map = get_map(fd);
	close(fd);
	return (game);
}

// only thing to think about is whether it's more efficient to put the character's coordinates as
// (0, 0) or something else. (then it must be the first element of the map should have (0,0) as its coordinates
// and character's position should be changed as soon as it moves.)
