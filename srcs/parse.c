/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/15 16:48:08 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_player_info(t_map *map, int *pos, char dir)
{
	map->pos.x = pos[0];
	map->pos.y = pos[1];
	if (dir == 'N')
		map->theta = 3 * PI / 2;
	else if (dir == 'S')
		map->theta = M_PI / 2;
	else if (dir == 'W')
		map->theta = PI;
	else
		map->theta = 0;
}

static void	put_info(t_map *map, char **map_data)
{
	int	max_width;
	int	i;
	int	j;
	char	*set_dir;
	
	max_width = 0;
	set_dir = "NSWE";
	i = -1;
	while (map_data[++i])
	{
		j = -1;
		while (map_data[i][++j])
		{
			if (ft_strchr(set_dir, map_data[i][j]))
				put_player_info(map, (int [2]) {i, j}, map_data[i][j]);
		}
		if (j > max_width)
			max_width = j;
	}
	map->height = i;
	map->width = max_width;
}

static bool **get_map_move(t_map map, char **charmap)
{
	int		i;
	int		j;
	bool	**res;

	res = ft_calloc(map.height, sizeof(bool *));
	i = -1;
	while (++i < map.height)
		res[i] = ft_calloc(map.width, sizeof(bool));
	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
			if (!(charmap[i][j] == ' ' || charmap[i][j] == '1' || charmap[i][j] == 'D'))
				res[i][j] = true;
	}
	return (res);
}


static char	**get_map_wall(t_map map, char **charmap)
{
	int		i;
	int		j;
	char	*set = "NSWE";
	char	**res;
	

	res = ft_calloc(map.height, sizeof(char *));
	i = -1;
	while (++i < map.height)
		res[i] = ft_calloc(map.width, sizeof(char));
	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			if (!charmap[i][j])
				while (j < map.width)
					res[i][j++] = '1';
			else if (ft_strchr(set, charmap[i][j]))
				res[i][j] = '0';
			else
				res[i][j] = charmap[i][j];
		}
	}
	return (res);
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
	put_info(&map, map_data);
	map.map_move = get_map_move(map, map_data);
	map.map_wall = get_map_wall(map, map_data);
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
	// game.info = parser(file);
	//game.draw = get_draw(fd);
	game.map = get_map(fd);
	close(fd);
	return (game);
}