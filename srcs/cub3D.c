/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/09 15:18:14 by min-kang         ###   ########.fr       */
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
}

void	hook_control(t_gui gui, t_hook *hook)
{
	hook->re = true;
	mlx_key_hook(gui.win, key_hook, &hook);
	mlx_mouse_hook(gui.win, mouse_hook, &hook);
	mlx_loop_hook(gui.mlx, &create_img, &gui);
}*/

int	terminate(t_game *game)
{
	(void) game;
	// free, close everything
	return (0);
}

int	cub3D(t_game game)
{	
	game.gui = initialize_window(100, 100, "cub3d_launching_test");
	// 1. minilibX initialize
	// 2. create images
	// 3. raycasting
	// 4. Hooks
	//hook_control(game.gui, &game.hook);
	//**draw
	for (int i = 2; i < 80; i++)
	//	mlx_pixel_put(&game.gui.mlx, &game.gui.win, i, i, 0x00FFFF00);
		my_mlx_pixel_put(&game.gui, i, i, 0x00FFFF00);
	mlx_put_image_to_window(game.gui.mlx, game.gui.win, game.gui.img, 0, 0);
	//**draw
	mlx_loop(game.gui.mlx);
	return (terminate(&game));
}
