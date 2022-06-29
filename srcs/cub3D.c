/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 23:57:27 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, "Cub3D");
	game->screen.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
	game->minimap.img = mlx_new_image(game->mlx, MINI_W, MINI_H);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bits_per_pixel, &game->minimap.line_length,
			&game->minimap.endian);
	game->hook.mouse_x_prev = SCREEN_X / 2;
	game->hook.minimap_on = 0;
	game->hook.minimap_size = 7;
	game->map.camera.dir_x = cos(game->map.theta);
	game->map.camera.dir_y = sin(game->map.theta) * -1;
	game->map.camera.plane_x = 0.66 * sin(game->map.theta) * -1;
	game->map.camera.plane_y = 0.66 * cos(game->map.theta);
}

static void	init_img(t_game *game)
{
	int			size_info[2];

	game->texture.wall_n.img = mlx_xpm_file_to_image(game->mlx,
			game->draw.nswe[0], &size_info[0], &size_info[1]);
	game->texture.wall_s.img = mlx_xpm_file_to_image(game->mlx,
			game->draw.nswe[1], &size_info[0], &size_info[1]);
	game->texture.wall_w.img = mlx_xpm_file_to_image(game->mlx,
			game->draw.nswe[2], &size_info[0], &size_info[1]);
	game->texture.wall_e.img = mlx_xpm_file_to_image(game->mlx,
			game->draw.nswe[3], &size_info[0], &size_info[1]);
	game->texture.door_o.img = mlx_xpm_file_to_image(game->mlx,
			"./texture/Door_o.xpm", &size_info[0], &size_info[1]);
	game->texture.door_c.img = mlx_xpm_file_to_image(game->mlx,
			"./texture/Door_c.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[0].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot1.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[1].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot2.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[2].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot3.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[3].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot4.xpm", &size_info[0], &size_info[1]);
	game->texture.spr[4].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot4.xpm", &size_info[0], &size_info[1]);	
	game->texture.spr[5].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot4.xpm", &size_info[0], &size_info[1]);	
	game->texture.spr[6].img = mlx_xpm_file_to_image(game->mlx,
			"./texture/robot4.xpm", &size_info[0], &size_info[1]);
}

static void	init_img_addr(t_game *game)
{
	game->texture.wall_n.addr = mlx_get_data_addr(game->texture.wall_n.img,
			&game->texture.wall_n.bits_per_pixel,
			&game->texture.wall_n.line_length, &game->texture.wall_n.endian);
	game->texture.wall_s.addr = mlx_get_data_addr(game->texture.wall_s.img,
			&game->texture.wall_s.bits_per_pixel,
			&game->texture.wall_s.line_length, &game->texture.wall_s.endian);
	game->texture.wall_w.addr = mlx_get_data_addr(game->texture.wall_w.img,
			&game->texture.wall_w.bits_per_pixel,
			&game->texture.wall_w.line_length, &game->texture.wall_w.endian);
	game->texture.wall_e.addr = mlx_get_data_addr(game->texture.wall_e.img,
			&game->texture.wall_e.bits_per_pixel,
			&game->texture.wall_e.line_length, &game->texture.wall_e.endian);
	game->texture.door_o.addr = mlx_get_data_addr(game->texture.door_o.img,
			&game->texture.door_o.bits_per_pixel,
			&game->texture.door_o.line_length, &game->texture.door_o.endian);
	game->texture.door_c.addr = mlx_get_data_addr(game->texture.door_c.img,
			&game->texture.door_c.bits_per_pixel,
			&game->texture.door_c.line_length, &game->texture.door_c.endian);
}

static void	init_spr_img(t_game *game)
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

int	cub3d(t_game game)
{
	init_game(&game);
	init_img(&game);
	init_img_addr(&game);
	init_spr_img(&game);
	begin_thread(&game);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	//mlx_hook(game.win, 6, 1L << 6, mouse_hook, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (terminate(&game));
}
