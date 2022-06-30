/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:18:52 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:25:43 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

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

static void	put_character(t_game *game, int border)
{
	void	*img;
	int		pos[2];

	img = mlx_xpm_file_to_image(game->mlx,
			"./texture/icon-character.xpm", &pos[0], &pos[1]);
	mlx_put_image_to_window(game->mlx, game->win,
		img, MINI_W / 2 + 4, MINI_H / 2 - border + 4);
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
