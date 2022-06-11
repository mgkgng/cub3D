/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/11 17:08:25 by mlecherb         ###   ########.fr       */
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

void	redraw(t_game *game)
{
	paint_background(game);
	draw_cub3D(game);
	mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.img, 0, 0);
	if (game->hook.minimap_on % 2)
		draw_minimap(game);
}

int	draw(t_game *game)
{
	int	i;
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
	return (0);
}

void	mouse_hook_control(t_game *game, t_hook *hook)
{	
	hook->m_re = true;
	mlx_hook(game->gui.win, 6, 1L << 6, mouse_hook, hook);
	mlx_loop_hook(game->gui.mlx, draw, game);
}

void	key_hook_control(t_game *game, t_hook *hook)
{
	hook->re = true;
	mlx_hook(game->gui.win, 2, 1L << 0, key_hook, game);
	mlx_loop_hook(game->gui.mlx, draw, game);
}

// int	door_count(char **map)
// {
// 	int	i;
// 	int	j;
// 	int	count;

// 	count = 0;
// 	i = -1;
// 	j = 0;
// 	while (map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		while (map[i][j] != '\0')
// 		{
// 			if (map[i][j] == '2')
// 				count++;
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	return (count);
// }

int	count_door(char **map)
{
	int	i;
	int j;
	int count;

	count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '2')
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}

t_point	*get_door(char **map, t_game game)
{
	t_point	*door;
	int	i;
	int	j;
	int	count;

	door = malloc(sizeof(t_point) * count_door(map));
	count = 0;
	i = 0;
	j = 0;
	while (map[i++])
	{
		while (map[i][j++])
		{
			if (map[i][j] == '2')
			{
				door[count].x = j;
				door[count++].y = i;
			}
		}
		j = 0;
	}
	game.nb_door = count;
	return (door);
}

int	cub3D(t_game game)
{		
	game.map.theta = M_PI / 2;
	game.draw.col_ceil = 0x00DA1FE9;
	game.draw.col_floor = 0x00000088;
	game.gui = initialize_window("cub3d_launching_test");
	game.hook.m_turn = 0;
	game.hook.x_prev = SCREEN_X / 2;
	game.hook.m_sensibility = 20;
	game.hook.minimap_on = 0;
	game.hook.minimap_size = 7;
	game.hook.move_re = STOP;
	game.t = t_init();
	game.t->img_wall = mlx_xpm_file_to_image(game.gui.mlx, "./texture/wall.xpm", &game.t->w, &game.t->h);
	game.t->img_door = mlx_xpm_file_to_image(game.gui.mlx, "./texture/Group-2.xpm", &game.t->w, &game.t->h);
	game.t->addr_wall = mlx_get_data_addr(game.t->img_wall, &game.t->bits_per_pixel, &game.t->line_length, &game.t->endian);
	game.t->addr_door = mlx_get_data_addr(game.t->img_door, &game.t->bits_per_pixel, &game.t->line_length, &game.t->endian);
	// game.map.mapchar = gm()
	game.map.door = get_door(game.map.mapchar, game);
	mouse_hook_control(&game, &game.hook);
	key_hook_control(&game, &game.hook);
	// mlx_hook(game.gui.mlx, 2, 1L << 0, &key_pressed, &game);
	// mlx_hook(game.gui.mlx, 3, 1L << 1, &key_released, &game);
	mlx_loop_hook(game.gui.mlx, &draw, &game);
	mlx_loop(game.gui.mlx);
	return (terminate(&game));
}
