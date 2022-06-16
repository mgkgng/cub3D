/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/16 16:48:58 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**get_lines(int fd)
{
	int		ret;
	char	buf[2];
	char	*line;

	ret = read(fd, buf, 1);
	buf[ret] = '\0';
	line = ft_strdup(buf);
	while (ret > 0)
	{
		ret = read(fd, buf, 1);
		buf[ret] = '\0';
		line = ft_strjoin(line, buf);
	}
	close(fd);
	return (ft_split(line, '\n'));
}

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

void	put_texture(char ***nswe, char **file)
{
	char	*nswe[4];
	int 	i;
	int 	checkfile;

	i = -1;
	while (++i < 4)
		if (i != verif_texture(file[i]) - 1)
			end_program("Wrong format for texture information.", 0);
	i = -1;
	while (++i < 4)
	{
		get_fd(file[i] + 3);
		*nswe[i] = ft_strdup(file[i] + 3);
	}
}

t_draw	get_draw(char **lines)
{
	t_draw	draw;
	int		i;
	
	i = -1;
	put_texture(&draw.nswe, lines);
	draw.col_floor = get_color(lines[4] + 2);
	draw.col_ceil = get_color(lines[5]);
	return (draw);
}

t_game	parse(char *filename)
{
	char	**lines;
	int		fd;
	t_game	game;
	
	if (!check_filename(filename))
		end_program("Wrong file format", 0);
	lines = get_lines(get_fd(filename));
	game.draw = get_draw(lines);
	game.map = get_map(lines);
	return (game);
}