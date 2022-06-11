/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:58:47 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/11 13:26:39 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	get_height(float dist, t_game *game)
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

// int	dist_door(t_game *game)
// {
	
// }

void	raycast(t_game *game, float angle, int rayN, t_text *t)
{
	t_raycast	ray;
	float tmp;
	// int side_x = 0;
	// int side_y = 0;

	// if (game->map.theta > PI && game->map.theta < PI * 2)
	// 	side_y--;
	// if (game->map.theta > PI / 2 && game->map.theta < PI / 2 * 3)
	// 	side_x--;
	tmp = 0;
	ray = digital_differential_analyzer(game->map, angle, game);
	// draw_raycast(game, get_height(ray.dist, game), rayN);
	// (void)t;
	// if (is_door(game->door, (int) ray.wall.x, (int) ray.wall.y, game) == 1)
	// 	printf("1\n");
	if (is_door(game->door, (int) ray.wall.x, (int) ray.wall.y, game))
	{
		tmp = perpendicular_dist((float [2]) {game->map.pos.x, game->map.pos.y}, (float [2]) {ray.wall.x, ray.wall.y}, game->map.theta + PI / 2);
		// printf("TMP : %f\n", tmp);
		if (tmp < game->min_door)
		{
			game->min_door = perpendicular_dist((float [2]) {game->map.pos.x, game->map.pos.y}, (float [2]) {ray.wall.x, ray.wall.y}, game->map.theta + PI / 2);
			game->pos[0] = (int)ray.wall.x;// - side_x;
			game->pos[1] = (int)ray.wall.y;// - side_y;
		}	
	}
	// printf("MIN : %f\n", game->min_door);
	draw_text(game, get_height(ray.dist, game), ray, rayN, t);	
}

void	draw_cub3D(t_game *game)
{
	float	start_angle;
	float	angle;
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
