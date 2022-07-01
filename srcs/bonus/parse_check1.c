/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:53:33 by min-kang          #+#    #+#             */
/*   Updated: 2022/07/01 14:47:27 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

static void	check_door(char **map, int i, int j)
{
	if (!i || !map[i + 1] || !j || !map[i][j + 1])
		end_program("Door shouldn't be at the border.", 0);
	if (map[i][j + 1] == '1' && map[i][j - 1] == '1')
		return ;
	if (map[i + 1][j] == '1' && map[i - 1][j] == '1')
		return ;
	end_program("Door must be surrounded on their side by a wall", 0);
}

static void	check_space(t_map *map, int i, int j)
{
	if ((i > 0 && !ft_strchr(" 1X", map->map_wall[i - 1][j]))
		|| (i < map->height - 1 && !ft_strchr(" 1X", map->map_wall[i + 1][j])))
		end_program("Space must be placed next to a wall or another space", 0);
	if ((j > 0 && !ft_strchr(" 1X", map->map_wall[i][j - 1]))
		|| (j < map->width - 1 && !ft_strchr(" 1X", map->map_wall[i][j + 1])))
		end_program("Space must be placed next to a wall or another space", 0);
}

void	check_map_horizontal(char **map)
{
	int		i;
	int		j;
	bool	open;

	i = -1;
	open = false;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((!i || !map[i + 1] || !j || !map[i][j + 1])
				&& ft_strchr("0NSWEZ", map[i][j]))
				end_program("The border of the map should be enclosed", 0);
			if (map[i][j] == 'D')
				check_door(map, i, j);
			if (!open && !ft_strchr(" 1", map[i][j]))
				open = true;
			if (open && map[i][j] == '1')
				open = false;
		}
		if (open)
			end_program("Error: The map is not surrounded.", 0);
	}	
}

void	check_map_vertical(t_map *map)
{
	int		i;
	int		j;
	bool	open;

	j = -1;
	open = false;
	while (++j < map->width)
	{
		i = -1;
		while (++i < map->height)
		{
			if (map->map_wall[i][j] == ' ')
				check_space(map, i, j);
			if (!open && !ft_strchr(" 1X", map->map_wall[i][j]))
				open = true;
			if (open && map->map_wall[i][j] == '1')
				open = false;
			if (map->map_wall[i][j] == 'X' && open)
				end_program("Error: The map is not surrounded v.", 0);
		}
		if (open)
			end_program("Error: The map is not surrounded v.", 0);
	}
}
