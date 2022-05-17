/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:58:47 by mlecherb          #+#    #+#             */
/*   Updated: 2022/05/17 18:14:34 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	get_height(double dist, t_game *game)
{
	int		h;

	h = (int)(SCREEN_Y / dist);
	if (h > SCREEN_Y)
	{
		game->height = h;
		h = SCREEN_Y;
	}
	else
		game->height = h;
	return (h);
}

void	draw_raycast(t_game *game, int h, int ray_x)
{
	int	start_y;
	int	i;

	start_y = (int)((SCREEN_Y - h) / 2);
	i = -1;
	printf("Start Y : %i\n", start_y);
	while (++i < h)
		my_mlx_pixel_put(&game->gui, ray_x, start_y + i, 0x00FFFF00);
}

void	raycast(t_game *game, double angle, int rayN, t_text *t)
{
	t_raycast	ray;
	double tmp;

	tmp = 0;
	ray = digital_differential_analyzer(game->map, angle);//, game);
	// draw_raycast(game, get_height(ray.dist, game), rayN);
	// (void)t;
	if (is_door(game->door, (int) ray.wall.x, (int) ray.wall.y, game) == 1)
		printf("1\n");
	if (is_door(game->door, (int) ray.wall.x, (int) ray.wall.y, game))
	{
		tmp = perpendicular_dist((double [2]) {game->map.pos.x, game->map.pos.y}, (double [2]) {ray.wall.x, ray.wall.y}, game->map.theta + PI / 2);
		// printf("TMP : %f\n", tmp);
		if (tmp < game->min_door)
		{
			game->min_door = perpendicular_dist((double [2]) {game->map.pos.x, game->map.pos.y}, (double [2]) {ray.wall.x, ray.wall.y}, game->map.theta + PI / 2);
			game->pos[0] = (int)ray.wall.x;
			game->pos[1] = (int)ray.wall.y;
		}	
	}
	// printf("MIN : %f\n", game->min_door);
	draw_text(game, get_height(ray.dist, game), ray, rayN, t);
	
}

void	draw_cub3D(t_game *game)
{
	double	start_angle;
	double	angle;
	int		ray;
	// t_text	*t;

	// t = t_init();
	// t->img = mlx_xpm_file_to_image(game->gui.mlx, "./texture/wall.xpm", &t->w, &t->h);
	// t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);

	start_angle = game->map.theta - ANGLE / 2;
	ray = -1;
	while (++ray < SCREEN_X)
	{
		angle = start_angle + (ray + 1) * ANGLE / SCREEN_X;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		raycast(game, angle, ray, game->t);
	}
}
