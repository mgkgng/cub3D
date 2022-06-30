/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:10:06 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:25:25 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

static void	init_obj_img(t_game *game)
{
	int	size_info[2];

	game->texture.door_o.img = mlx_xpm_file_to_image(game->mlx,
			"./texture/door_o.xpm", &size_info[0], &size_info[1]);
	game->texture.door_c.img = mlx_xpm_file_to_image(game->mlx,
			"./texture/door_c.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[0].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot1.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[1].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot2.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[2].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot3.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[3].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot4.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[4].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot5.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[5].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot6.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[6].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot7.xpm", &size_info[0], &size_info[1]);
}

static void	init_door_img_addr(t_game *game)
{
	game->texture.door_o.addr = mlx_get_data_addr(game->texture.door_o.img,
			&game->texture.door_o.bits_per_pixel,
			&game->texture.door_o.line_length, &game->texture.door_o.endian);
	game->texture.door_c.addr = mlx_get_data_addr(game->texture.door_c.img,
			&game->texture.door_c.bits_per_pixel,
			&game->texture.door_c.line_length, &game->texture.door_c.endian);
}

static void	init_spr_img_addr(t_game *game)
{
	game->texture.spr[0].addr = mlx_get_data_addr(game->texture.spr[0].img,
			&game->texture.spr[0].bits_per_pixel,
			&game->texture.spr[0].line_length, &game->texture.spr[0].endian);
	game->texture.spr[1].addr = mlx_get_data_addr(game->texture.spr[1].img,
			&game->texture.spr[1].bits_per_pixel,
			&game->texture.spr[1].line_length, &game->texture.spr[0].endian);
	game->texture.spr[2].addr = mlx_get_data_addr(game->texture.spr[2].img,
			&game->texture.spr[2].bits_per_pixel,
			&game->texture.spr[2].line_length, &game->texture.spr[2].endian);
	game->texture.spr[3].addr = mlx_get_data_addr(game->texture.spr[3].img,
			&game->texture.spr[3].bits_per_pixel,
			&game->texture.spr[3].line_length, &game->texture.spr[3].endian);
	game->texture.spr[4].addr = mlx_get_data_addr(game->texture.spr[4].img,
			&game->texture.spr[4].bits_per_pixel,
			&game->texture.spr[4].line_length, &game->texture.spr[4].endian);
	game->texture.spr[5].addr = mlx_get_data_addr(game->texture.spr[5].img,
			&game->texture.spr[5].bits_per_pixel,
			&game->texture.spr[5].line_length, &game->texture.spr[5].endian);
	game->texture.spr[6].addr = mlx_get_data_addr(game->texture.spr[6].img,
			&game->texture.spr[6].bits_per_pixel,
			&game->texture.spr[6].line_length, &game->texture.spr[6].endian);
}

void	init_bonus(t_game *game)
{
	init_obj_img(game);
	init_door_img_addr(game);
	init_spr_img_addr(game);
}
