/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 00:44:46 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, "Cub3D");
	game->gui.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->gui.addr = mlx_get_data_addr(game->gui.img, &game->gui.bits_per_pixel, &game->gui.line_len, &game->gui.endian);
	//* here is for the bonus
	game->minimap.img = mlx_new_image(game->mlx, MINI_W, MINI_H);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->minimap.bits_per_pixel, &game->minimap.line_len, &game->minimap.endian); 
	//* bonus
}

void	initialize_hook(t_game *game)
{
	game->hook.m_turn = 0;
	game->hook.x_prev = SCREEN_X / 2;
	game->hook.m_sensibility = 20;
	game->hook.minimap_on = 0;
	game->hook.minimap_size = 7;
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

void	sprite(t_game *game)
{
	t_sprite *tmp;
	int	i;

	tmp = game->spr;
	i = 0;
	if (game->sprite == 5)
	{
		game->lock = 0;
		game->sprite = 0;
	}
	while (i < game->sprite)
	{
		i++;
		tmp  = tmp->next;
	}
	game->sprite++;
	mlx_put_image_to_window(game->mlx, game->win, tmp->img, SCREEN_X / 2, SCREEN_Y / 2);
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
	game.texture = get_texture_img(game.draw, game.mlx);
	game.lock = 0;
	game.count = 0;
	game.key = malloc(sizeof(t_key));
	mouse_hook_control(&game, &game.hook);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (terminate(&game));
}
