/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:18:52 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/09 14:39:00 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// for minimap i have to recreate an image.

static void	fill_void(t_game *game, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINI_W)
	{
		j = -1;
		while (++j < MINI_H)
			minimap_pixel_put(&game->gui, i, j, color);
	}
}
/*static void	draw_grid_v1(t_game *game, int case_nb, int color)
{
	int start_x = (game->map.pos.x - case_nb / 2) * MINI_SQUARE;
	int	start_y = (game->map.pos.y - case_nb / 2) * MINI_SQUARE;
	int	i;
	int	j;

	printf("%d... %d...\n", start_x, start_y);
	i = -1;
	while (++i < MINI_W)
	{
		j = -1;
		while (++j < MINI_H)
		{
			if (!((start_x + i) % MINI_SQUARE))
				minimap_pixel_put(&game->gui, start_x + i, start_y + j, color);
			else if (!((start_x + j) % MINI_SQUARE))
				minimap_pixel_put(&game->gui, start_x + i, start_y + j, color);

		}
	}
}*/

/*static void	draw_square(t_game *game, int *where, int size, int color)
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
}*/

/*static void	draw_map(t_game *game, int blen)
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
}*/

/*static void	draw_red(t_game *game, int blen)
{
	draw_square(game, (int [2]){MINI_X + game->map.pos.x * blen,
		MINI_Y + game->map.pos.y * blen}, 3, 0x22FF0000);
}*/

static void	put_virus(t_game *game)
{
	void	*img;
	int		pos[2];
	
	img = NULL;
	img = mlx_xpm_file_to_image(game->gui.mlx, "./texture/virus_48x48.xpm", &pos[0], &pos[1]);
//	mlx_put_image_to_window(game->gui.mlx, game->gui.win, img, MINI_X + game->map.pos.x * blen, MINI_Y + game->map.pos.y * blen);
	mlx_put_image_to_window(game->gui.mlx, game->gui.win, img, MINI_W / 2, MINI_H / 2);

}	

void	draw_minimap(t_game *game)
{
	int	blockLength;

	ft_bzero(game->gui.mini_addr, MINI_W * MINI_H * 4);
	// maybe need to decide again beginning point of miniX and miniY according to the blockLength
	blockLength = MINI_W / game->map.width;
	if (blockLength > MINI_H / game->map.height)
		blockLength = MINI_H / game->map.height;
	//printf("blockLength====%d\n", blockLength);
	//draw_map(game, blockLength);
	fill_void(game, 0x8887ceeb);
	//draw_grid_v1(game, 5, 0xFFFFFF);
	mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.mini_img, MINI_X, MINI_Y);
	put_virus(game);
}