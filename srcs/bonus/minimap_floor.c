/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:54:31 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:25:39 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

static bool	wall_condition(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height
		|| (!map->map_move[y][x] && !ft_strchr("DZ", map->map_wall[y][x])))
		return (true);
	return (false);
}

static void	draw_square(t_game *game, int *where, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (++i < size - 1)
	{
		j = 0;
		while (++j < size - 1)
			put_pixel(&game->minimap, where[0] + j, where[1] + i, color);
	}
}

static void	put_obj_icon(t_game *game, int x, int y, int sprite)
{
	int		pos[2];
	void	*img;

	if (sprite)
		img = mlx_xpm_file_to_image(game->mlx,
				"./texture/icon-robot.xpm", &pos[0], &pos[1]);
	else
		img = mlx_xpm_file_to_image(game->mlx,
				"./texture/icon-door.xpm", &pos[0], &pos[1]);
	mlx_put_image_to_window(game->mlx, game->win,
		img, x + 22, y + 22);
}

void	fill_floor(t_game *game, int size, int color)
{
	int	x_init;
	int	y_init;
	int	i;
	int	j;

	x_init = (int) game->map.pos.x - size / 2;
	y_init = (int) game->map.pos.y - size / 2;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (wall_condition(&game->map, x_init + i, y_init + j))
				draw_square(game, (int [2]){i * MINI_W / size,
					j * MINI_H / size}, MINI_W / size, color);
			else if (game->map.map_wall[y_init + j][x_init + i] == 'Z')
				put_obj_icon(game, i * MINI_W / size, j * MINI_H / size, 1);
			else if (game->map.map_wall[y_init + j][x_init + i] == 'D'
				&& !game->map.map_move[y_init + j][x_init + i])
				put_obj_icon(game, i * MINI_W / size, j * MINI_H / size, 0);
		}
	}
}
