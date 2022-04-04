/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:20:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/05 01:49:29 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
typedef struct s_gui {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
} 	t_gui;
*/

t_gui	initialize_window(int width, int height, const char *game_name)
{
	t_gui	gui;

	gui.game_width = width;
	gui.game_height = height;
	gui.mlx = mlx_init();
	gui.win = mlx_new_window(gui.mlx, width, height, game_name);
	gui.img = mlx_new_image(gui.mlx, width, height);
	gui.addr = mlx_get_data_addr(gui.img, &gui.bits_per_pixel, &gui.line_len, &gui.endian);
	ft_bzero(&gui.hook, sizeof(t_hook));
	gui.hook.re = true;
	return (gui);
}

void	create_img(t_gui *gui)
{
	if (gui->hook.re)
	{
		ft_bzero(gui.addr, gui.game_width * gui->game_height * gui.bits_per_pixel);
		/*
		...
		here we draw
		...
		*/
		gui->hook.re = false;
	}
}

void	hook_control(t_gui *gui, t_hook *hook)
{
	hook->re = true;
	mlx_key_hook(gui.win, key_hook, &hook);
	mlx_mouse_hook(gui.win, mous_hook, &hook);
	mlx_loop_hook(main.vars.mlx, create_game, &gui);
}

int	terminate(t_gui *gui)
{
	// free, close everything
	return (0);
}

int	cub3D(t_game game)
{
	t_gui	gui;
	
	gui = initialize_window(1920, 1080, "cub3d_launching_test");
	// 1. minilibX initialize
	// 2. create images
	// 3. raycasting
	// 4. Hooks
	hook_control(&gui, &gui.hook);
	mlx_loop(gui.mlx);
	return (terminate(&gui));
}
