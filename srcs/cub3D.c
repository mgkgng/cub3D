/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:10 by min-kang         ###   ########.fr       */
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
	game->min_door = INT32_MAX;
	paint_background(game);
	draw_cub3D(game);
	mlx_put_image_to_window(game->gui.mlx, game->gui.win, game->gui.img, 0, 0);
	if (game->hook.minimap_on % 2)
		draw_minimap(game);
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
	mlx_put_image_to_window(game->gui.mlx, game->gui.win, tmp->img, SCREEN_X / 2, SCREEN_Y / 2);
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
	if (game->lock == 1 && game->count % 2 == 0)
		sprite(game); // A REGLER.
	game->count++;
	return (0);
}

void	mouse_hook_control(t_game *game, t_hook *hook)
{	
	hook->m_re = true;
	mlx_hook(game->gui.win, 6, 1L << 6, mouse_hook, hook);
	// mlx_loop_hook(game->gui.mlx, draw, game);
}

void	key_hook_control(t_game *game, t_hook *hook)
{
	hook->re = true;
	mlx_hook(game->gui.win, 2, 1L << 0, key_hook, game);
	// mlx_loop_hook(game->gui.mlx, draw, game);
}

t_sprite	*ft_lstnew(char *name, t_game *game)
{
	t_sprite	*new;

	new = malloc(sizeof(t_sprite));
	if (new == NULL)
		return (NULL);
	new->h = 64;
	new->w = 64;
	new->img = mlx_xpm_file_to_image(game->gui.mlx, name, &new->w, &new->h);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, &new->line_length, &new->endian);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_sprite **alst, t_sprite *new)
{
	t_sprite	*temp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	else
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	init_sprite(t_game *game)
{
	game->spr = ft_lstnew("./sprite/Couche-1.xpm", game);
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-2.xpm", game));
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-3.xpm", game));
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-4.xpm", game));
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-5.xpm", game));
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
	game.texture = get_texture(game.gui.mlx);
	init_sprite(&game);
	game.lock = 0;
	game.count = 0;
	mouse_hook_control(&game, &game.hook);
	key_hook_control(&game, &game.hook);
	// draw(&game);
	mlx_loop_hook(game.gui.mlx, draw, &game);
	mlx_loop(game.gui.mlx); // BOUCLER SUR DRAW
	return (terminate(&game));
}
