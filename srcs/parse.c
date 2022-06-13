/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/13 17:26:28 by mlecherb         ###   ########.fr       */
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

static void	put_info(t_map *map, char **map_data)
{
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

	boolmap = ft_calloc(map_height, sizeof(bool *));
	i = -1;
	while (++i < map_height)
		boolmap[i] = ft_calloc(map_width, sizeof(bool));
	i = -1;
	while (++i < map_height)
	{
		j = -1;
		while (++j < map_width)
		{
			if (!charmap[i][j])
				break;
			if (!(charmap[i][j] == ' ' || charmap[i][j] == '1' || charmap[i][j] == '2'))
				boolmap[i][j] = true;
		}
	}
	return (boolmap);
}

static t_point *get_doors(char **charmap, int map_width, int map_height)
{
	int		count;
	int		i;
	int		j;
	t_point	*res;

	res = NULL;
	count = 0;
	i = -1;
	while (++i < map_height)
	{
		j = -1;
		while (++j < map_width)
		{
			if (charmap[i][j] == 'D')
			{
				if (!res)
					res = malloc(sizeof(t_point));
				else
					ft_realloc(res, ++count * sizeof(t_point));
				res[count - 1].x = j;
				res[count - 1].y = i;
			}
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
	is_surrounded(map_data);
	if (!check_fileformat(mapstr, map_data))
		error(4);
	put_info(&map, map_data);
	map.map2d = get_boolmap(map_data, map.width, map.height);
	map.doors = get_doors(map_data, map.width, map.height);
	free(map_data);
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
			break;
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

// only thing to think about is whether it's more efficient to put the character's coordinates as
// (0, 0) or something else. (then it must be the first element of the map should have (0,0) as its coordinates
// and character's position should be changed as soon as it moves.)
