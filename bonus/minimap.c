/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:18:52 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/29 19:22:38 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// for minimap i have to recreate an image.

static void	draw_square(t_game *game, int *where, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			minimap_pixel_put(&game->gui, where[0] + j, where[1] + i, color);
	}
}

static void	draw_map(t_game *game, int blen)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (game->map.map2d[i][j])
			{
				draw_square(game, (int [2]) {blen * j,
					MINI_Y + blen * i}, blen, 0x88FFFFFF);
			}
			else
				draw_square(game, (int [2]) {blen * j,
					MINI_Y + blen * i}, blen, 0xFFFFFFFF);

		}
	}
}

static void	draw_red(t_game *game, int blen)
{
	draw_square(game, (int [2]){MINI_X + game->map.pos.x * blen,
		MINI_Y + game->map.pos.y * blen}, 3, 0x22FF0000);
}

void	draw_minimap(t_game *game)
{
	int	blockLength;

	// maybe need to decide again beginning point of miniX and miniY according to the blockLength
	blockLength = MINI_W / game->map.width;
	if (blockLength > MINI_H / game->map.height)
		blockLength = MINI_H / game->map.height;
	//printf("blockLength====%d\n", blockLength);
	draw_map(game, blockLength);
	draw_red(game, blockLength);
	mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.mini_img, MINI_X, MINI_Y);
}