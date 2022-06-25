/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:53:33 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/25 20:41:29 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void check_space(char **map, int i, int j)
{
	if ((i > 0 && !ft_strchr(" 1", map[i - 1][j]))
		|| (map[i + 1] && !ft_strchr(" 1", map[i + 1][j])))
		end_program("Space must be placed next to the wall or another space", 0);
	if ((j > 0 && !ft_strchr(" 1", map[i][j - 1]))
		|| (map[i][j + 1] && !ft_strchr(" 1", map[i][j + 1])))
		end_program("Space must be placed next to the wall or another space", 0);
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
			if (map[i][j] == ' ')
				check_space(map, i, j);
			if (!open && !ft_strchr(" 1", map[i][j]))
				open = true;
			if (open && map[i][j] == '1')
				open = false;
		}
		printf("   %dth line, open value = %d\n", i, open);
		if (open)
			end_program("Error: The map is not surrounded.", 0);
	}	
}

void	check_map_vertical(t_map *map)
{
	int		i;
	int		j;
	bool	open;
	
	width = 0;
	i = -1;

		i = -1;
		while (map[++i])
		{	
			if (!open && !(map[i][j] == ' ' || map[i][j] == '1'))
				open = true;
			if (open && map[i][j] == '1')
				open = false;
		}
		if (open)
			end_program("Error: The map is not surrounded.", 0);
	}
}