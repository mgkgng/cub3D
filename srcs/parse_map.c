/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <min-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:42:50 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/27 21:21:16 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_player_info(t_map *map, int *pos, char dir, int *dir_n)
{
	map->pos.x = pos[1] + 0.5;
	map->pos.y = pos[0] + 0.5;
	if (dir == 'N')
		map->theta = 3 * PI / 2;
	else if (dir == 'S')
		map->theta = M_PI / 2;
	else if (dir == 'W')
		map->theta = PI;
	else
		map->theta = 0;
	(*dir_n)++;
}

static void	put_info(t_map *map, char **map_data)
{
	int	max_width;
	int	i;
	int	j;
	int	dir_n;

	dir_n = 0;
	max_width = 0;
	i = -1;
	while (map_data[++i])
	{
		j = -1;
		while (map_data[i][++j])
			if (ft_strchr("NSWE", map_data[i][j]))
				put_player_info(map, (int [2]){i, j}, map_data[i][j], &dir_n);
		if (j > max_width)
			max_width = j;
	}
	if (!dir_n)
		end_program("Error: no position indicator(NSWE)", 0);
	if (dir_n > 1)
		end_program("Error: more than one position indicator(NSWE)", 0);
	map->height = i;
	map->width = max_width;
	if (map->height < 3 || map->width < 3)
		end_program("Error: the map is too small", 0);
}

static bool	**get_map_move(t_map map, char **charmap)
{
	int		i;
	int		j;
	bool	**res;

	res = ft_calloc(map.height, sizeof(bool *));
	i = -1;
	while (charmap[++i])
		res[i] = ft_calloc(map.width, sizeof(bool));
	i = -1;
	while (charmap[++i])
	{
		j = -1;
		while (charmap[i][++j])
		{
			if (!ft_strchr("NSWEDZ01 ", charmap[i][j]))
				end_program("Error: Unknown character present on the map", 0);
			if (!(ft_strchr(" 1DZ", charmap[i][j])))
				res[i][j] = true;
		}
	}
	return (res);
}

static char	**get_map_wall(t_map map, char **charmap)
{
	int		i;
	int		j;
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
					res[i][j++] = 'X';
			else if (ft_strchr("NSWE", charmap[i][j]))
				res[i][j] = '0';
			else
				res[i][j] = charmap[i][j];
		}
	}
	return (res);
}

t_map	get_map(char **lines)
{
	t_map	map;

	put_info(&map, lines + 6);
	map.map_move = get_map_move(map, lines + 6);
	map.map_wall = get_map_wall(map, lines + 6);
	map.spr = get_sprite(lines + 6);
	check_map_horizontal(lines + 6);
	check_map_vertical(&map);
	return (map);
}
