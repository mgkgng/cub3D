/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/10 17:50:18 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_gui	initialize_window(int width, int height, char *game_name)
{
	t_gui	gui;

	gui.game_width = width;
	gui.game_height = height;
	gui.mlx = mlx_init();
	gui.win = mlx_new_window(gui.mlx, width, height, game_name);
	gui.img = mlx_new_image(gui.mlx, width, height);
	gui.addr = mlx_get_data_addr(gui.img, &gui.bits_per_pixel, &gui.line_len, &gui.endian);
	//ft_bzero(&gui.hook, sizeof(t_hook));
	//gui.hook.re = true;
	return (gui);
}

/*int	create_img(t_gui *gui)
{
	if (gui->hook.re)
	{
		ft_bzero(gui.addr, gui.game_width * gui->game_height * gui.bits_per_pixel);
		
		...
		here we draw
		...
		
		gui->hook.re = false;
	}
}*/

int	terminate(t_game *game)
{
	//** map not yet used for testing
	//free(game->map.map2d);
	(void) game;
	exit(0);
}

int	draw_cub3D(t_game *game)
{
	if (game->hook.re)
	{
		ft_bzero(game->gui.addr, 500 * 500 * 4);
		my_mlx_pixel_put(&game->gui, game->map.pos.x, game->map.pos.y, 0x00FFFF00);
		for (int i = 0; i < 8; i++)
		{
			my_mlx_pixel_put(&game->gui, game->map.pos.x + i * cos(game->map.theta), game->map.pos.y + i * sin(game->map.theta), 0x00FF9900);
		
		}
		mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.img, 0, 0);
		game->hook.re = false;
	}
	return (0);
}	

void	hook_control(t_game *game, t_hook *hook)
{
	hook->re = true;
	mlx_hook(game->gui.win, 2, 1L << 0, key_hook, game);
	//mlx_key_hook(game->gui.win, key_hook, hook);
	mlx_loop_hook(game->gui.mlx, draw_cub3D, game);
}

int	cub3D(t_game game)
//int	cub3D(void)
{		
	game.map.theta = M_PI_4;
	game.gui = initialize_window(500, 500, "cub3d_launching_test");
	// 1. minilibX initialize
	// 2. create images
	// 3. raycasting
	// 4. Hooks
	hook_control(&game, &game.hook);
	//**draw
	draw_cub3D(&game);
	//**draw
	mlx_loop(game.gui.mlx);
	return (terminate(&game));
}
