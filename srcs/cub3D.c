/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 23:17:23 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, "Cub3D");
	game->gui.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->gui.addr = mlx_get_data_addr(game->gui.img, &game->gui.bits_per_pixel, &game->gui.line_len, &game->gui.endian);
	// bonus
	game->minimap.img = mlx_new_image(game->mlx, MINI_W, MINI_H);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->minimap.bits_per_pixel, &game->minimap.line_len, &game->minimap.endian); 
}

void	initialize_hook(t_game *game)
{
	game->hook.m_turn = 0;
	game->hook.x_prev = SCREEN_X / 2;
	game->hook.m_sensibility = 20;
	game->hook.minimap_on = 0;
	game->hook.minimap_size = 7;
}

void	initialize_texture(t_game *game)
{
	int			size_info[2];

	game->texture.wall_n.img = mlx_xpm_file_to_image(game->mlx, game->draw.nswe[0], &size_info[0], &size_info[1]);
	game->texture.wall_s.img = mlx_xpm_file_to_image(game->mlx, game->draw.nswe[1], &size_info[0], &size_info[1]);
	game->texture.wall_w.img = mlx_xpm_file_to_image(game->mlx, game->draw.nswe[2], &size_info[0], &size_info[1]);
	game->texture.wall_e.img = mlx_xpm_file_to_image(game->mlx, game->draw.nswe[3], &size_info[0], &size_info[1]);
	game->texture.door.img = mlx_xpm_file_to_image(game->mlx, "./texture/Door_final.xpm", &size_info[0], &size_info[1]);
	game->texture.wall_n.addr = mlx_get_data_addr(game->texture.wall_n.img, &game->texture.wall_n.bits_per_pixel, &game->texture.wall_n.line_length, &game->texture.wall_n.endian);
	game->texture.wall_s.addr = mlx_get_data_addr(game->texture.wall_s.img, &game->texture.wall_s.bits_per_pixel, &game->texture.wall_s.line_length, &game->texture.wall_s.endian);
	game->texture.wall_w.addr = mlx_get_data_addr(game->texture.wall_w.img, &game->texture.wall_w.bits_per_pixel, &game->texture.wall_w.line_length, &game->texture.wall_w.endian);
	game->texture.wall_e.addr = mlx_get_data_addr(game->texture.wall_e.img, &game->texture.wall_e.bits_per_pixel, &game->texture.wall_e.line_length, &game->texture.wall_e.endian);
	game->texture.door.addr = mlx_get_data_addr(game->texture.door.img, &game->texture.door.bits_per_pixel, &game->texture.door.line_length, &game->texture.door.endian);
}

int	redraw(t_game *game)
{
	paint_background(game);
	draw_cub3D(game);
	mlx_put_image_to_window(game->mlx, game->win, game->gui.img, 0, 0);
	if (game->hook.minimap_on % 2)
		draw_minimap(game);
	return (0);
}

int	draw(t_game *game)
{
	int	i;

	movement(game);
	if (game->hook.re)
	{
		redraw(game);
		game->hook.re = false;
	}
	if (game->hook.m_re)
	{
		i = -1;
		while (++i * game->hook.m_sensibility < game->hook.m_turn)
		{
			turn(&game->map, game->hook.m_dir);
			redraw(game);
		}
		game->hook.m_re = false;
	}
	if (game->lock == 1 && game->count % 2 == 0)
		sprite(game); // A REGLER.
	game->count++;
	return (0);
}

void	mouse_hook_control(t_game *game, t_hook *hook)
{	
	hook->m_re = true;
	mlx_hook(game->win, 6, 1L << 6, mouse_hook, hook);
	// mlx_loop_hook(game->gui.mlx, draw, game);
}

int	cub3D(t_game game)
{
	initialize_window(&game);
	initialize_hook(&game);
	initialize_texture(&game);
	mouse_hook_control(&game, &game.hook);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (terminate(&game));
}
