/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/03 23:38:56 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_gui	initialize_window(char *game_name)
{
	t_gui	gui;

	gui.mlx = mlx_init();
	gui.win = mlx_new_window(gui.mlx, SCREEN_X, SCREEN_Y, game_name);
	gui.img = mlx_new_image(gui.mlx, SCREEN_X, SCREEN_Y);
	gui.addr = mlx_get_data_addr(gui.img, &gui.bits_per_pixel, &gui.line_len, &gui.endian);
	//* here is for the bonus
	gui.mini_img = mlx_new_image(gui.mlx, MINI_W, MINI_H);
	gui.mini_addr = mlx_get_data_addr(gui.mini_img, &gui.mini_pixel, &gui.mini_len, &gui.mini_endian); 
	//* bonus
	//ft_bzero(&gui.hook, sizeof(t_hook));
	//gui.hook.re = true;
	return (gui);
}

int	terminate(t_game *game)
{
	free(game->map.map2d);
	exit(0);
}

void	paint_background(t_game *game)
{
	int	i;
	int	j;

	j = -1;
	while (++j < SCREEN_Y / 2)
	{
		i = -1;
		while (++i < SCREEN_X)
			my_mlx_pixel_put(&game->gui, i, j, game->draw.col_ceil);
	}
	j--;
	while (++j < SCREEN_Y)
	{
		i = -1;
		while (++i < SCREEN_X)
			my_mlx_pixel_put(&game->gui, i, j, game->draw.col_floor);
	}	
}

int	draw(t_game *game)
{
	if (game->hook.re)
	{
		//ft_bzero(game->gui.addr, SCREEN_X * SCREEN_Y * 4);
		paint_background(game);
		draw_cub3D(game);
		mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.img, 0, 0);
		//* for bonus
		//if (game->hook.minimapOn)
		draw_minimap(game);
		//* bonus
		game->hook.re = false;
	}
	return (0);
}

void	mouse_hook_control(t_game *game, t_hook *hook)
{
	int	i;
	
	mlx_hook(game->gui.win, 6, 1L << 6, mouse_hook, game);
	i = 0;
	while (i++ * hook->m_sensibility < hook->m_turn)
	{
		paint_background(game);
		draw_cub3D(game);
		mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.img, 0, 0);
		draw_minimap(game);
		//mlx_loop_hook(game->gui.mlx, draw, game);
		printf("toto\n");
	}
}

void	key_hook_control(t_game *game, t_hook *hook)
{
	hook->re = true;
	mlx_hook(game->gui.win, 2, 1L << 0, key_hook, game);
	mlx_loop_hook(game->gui.mlx, draw, game);
}

int	cub3D(t_game game)
{		
	game.map.theta = M_PI / 2;
	game.draw.col_ceil = 0x00008800;
	game.draw.col_floor = 0x00000088;
	game.gui = initialize_window("cub3d_launching_test");
	game.hook.m_turn = 0;
	game.hook.x_prev = SCREEN_X / 2;
	game.hook.m_sensibility = 10;
	mouse_hook_control(&game, &game.hook);
	key_hook_control(&game, &game.hook);
	draw(&game);
	mlx_loop(game.gui.mlx);
	return (terminate(&game));
}
