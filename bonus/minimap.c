/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:18:52 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 18:22:58 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_void(t_game *game, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINI_W)
	{
		j = -1;
		while (++j < MINI_H)
			put_pixel(&game->minimap, i, j, color);
	}
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

static void	fill_floor(t_game *game, int size, int color)
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
			if (x_init + i < 0 || x_init + i >= game->map.width
				|| y_init + j < 0 || y_init + j >= game->map.height
				|| !game->map.map_move[y_init + j][x_init + i])
				draw_square(game, (int [2]){i * MINI_W / size,
					j * MINI_H / size}, MINI_W / size, color);
		}
	}
}

static void	put_character(t_game *game, int border)
{
	void	*img;
	int		pos[2];

	img = NULL;
	img = mlx_xpm_file_to_image(game->mlx,
			"./texture/Suisse.xpm", &pos[0], &pos[1]);
	mlx_put_image_to_window(game->mlx, game->win,
		img, MINI_W / 2, MINI_H / 2 - border);
}	

void	draw_minimap(t_game *game)
{
	ft_bzero(game->minimap.addr, MINI_W * MINI_H * 4);
	fill_void(game, 0x8887ceeb);
	fill_floor(game, game->hook.minimap_size, 0x44505050);
	mlx_put_image_to_window(game->mlx, game->win,
		game->minimap.img, MINI_X, MINI_Y);
	put_character(game, MINI_X / game->hook.minimap_size);
}
