/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/28 12:19:37 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall(t_game *game, t_ray ray, int ray_n, float angle)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info		info;
	int				i;

	h = get_height(ray.dist, game);
	if (game->height > 600)
		h = h / ray.dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(ray.wall, h, start);
	info.img = which_texture(ray.wall_side, &game->texture, angle);
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		put_pixel(&game->screen, ray_n, start + i, color);
	}
}

static void	draw_door(t_game *game, t_list *obj, int ray_n)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info		info;
	int				i;

	h = get_height(obj->dist, game);
	if (game->height > 600)
		h = h / obj->dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(obj->pos, h, start);
	if (game->map.map_move[(int) obj->map_pos.y][(int) obj->map_pos.x] == false)
		info.img = game->texture.door_c;
	else
		info.img = game->texture.door_o;
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		put_pixel(&game->screen, ray_n, start + i, color);
	}
}

static void	draw_ray(t_game *game, t_ray *ray, int ray_x, float angle)
{
	t_list	*current_obj;

	draw_wall(game, *ray, ray_x, angle);
	current_obj = ray->object;
	while (current_obj)
	{
		if (current_obj->type == DOOR)
			draw_door(game, current_obj, ray_x);
		current_obj = current_obj->next;
	}
	free_list(ray->object);
}

int	find_max_index(float *dist, int nb, int already)
{
	int	i;
	int	max;
	int	res;

	i = -1;
	max = INT32_MIN;
	res = 0;
	while (++i < nb)
	{
		if (dist[i] > max && (already == -1 || dist[i] < dist[already]))
		{
			max = dist[i];
			res = i;
		}
	}
	return (res);
}

int	*sort_sprites(float *dist, int nb)
{
	int	i;
	int	*res;
	int	already;
	int	max;

	res = ft_calloc(nb, sizeof(int));
	i = -1;
	already = -1;
	while (++i < nb)
	{
		max = find_max_index(dist, nb, already);
		res[i] = max;
		already = max;
	}
	return (res);
}

void	draw_sprite(t_game *game, float *dist, t_img img)
{
	int	sprite_nb;
	int	i;

	if (!game->map.spr)
		return ;
	sprite_nb = 0;
	i = -1;
	while (game->map.spr[++i].x != -1)
		sprite_nb++;
	float	*spr_dist = ft_calloc(sprite_nb, sizeof(float));
    //SPRITE CASTING
    //sort sprites from far to close
    for(int i = 0; i < sprite_nb; i++)
    {
		spr_dist[i] = pow(game->map.pos.x - game->map.spr[i].x, 2)
			+ pow(game->map.pos.y - game->map.spr[i].y, 2);
		printf("spr distance %d: %f\n", i, spr_dist[i]);
	}
	int *spr_sort = sort_sprites(spr_dist, sprite_nb);

    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < sprite_nb; i++)
	{
      //translate sprite position to relative to camera
		float spr_x = game->map.spr[spr_sort[i]].x - game->map.pos.x;
		float spr_y = game->map.spr[spr_sort[i]].y - game->map.pos.y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

		float invDet = 1.0 / (game->camera.plane_x * game->camera.dir_y - game->camera.dir_x * game->camera.plane_y); //required for correct matrix multiplication

		float transform_x = invDet * (game->camera.dir_y * spr_x - game->camera.dir_x * spr_y);
		float transform_y = invDet * (game->camera.plane_x * spr_y - game->camera.plane_y * spr_x); //this is actually the depth inside the screen, that what Z is in 3D

		int spr_screen_x = (int)((SCREEN_X / 2) * (1 + transform_x / transform_y));

      //calculate height of the sprite on screen
		int spr_h = abs((int) (SCREEN_Y / transform_y)); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
		int start_y = (SCREEN_Y - spr_h) / 2;
		if(start_y < 0)
			start_y = 0;
		int end_y = (SCREEN_Y + spr_h) / 2;
		if(end_y >= SCREEN_Y)
		end_y = SCREEN_Y - 1;

      //calculate width of the sprite
		int spr_width = abs((int) (SCREEN_Y / transform_y));
		int start_x = spr_screen_x - spr_width / 2;
		if (start_x < 0)
			start_x = 0;
		int end_x = spr_width / 2 + spr_screen_x;
		if (end_x >= SCREEN_X)
			end_x = SCREEN_X - 1;

		int	i = start_x - 1;
		printf("so %d... %d...\n", i, end_x);
		while (++i < end_x)
		{
			printf("it goes\n");
			int tex_x = (int)(256 * (i - (spr_screen_x - spr_width / 2)) * 64 / spr_width) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transform_y > 0 && i > 0 && i < SCREEN_X && transform_y < dist[i])
			{
				int j = start_y - 1;
				while (++j < end_y) //for every pixel of the current stripe
				{
					printf("to see\n");
					int d = j * 256 - SCREEN_Y * 128 + spr_h * 128; //256 and 128 factors to avoid floats
					int tex_y = ((d * 64) / spr_h) / 256;
					unsigned int color = get_data_color(tex_x, 64 * tex_y, img.addr, img);
					put_pixel(&game->screen, i, j, color);
				}
			}
		}
	}
}

static void	draw_by_ray(t_game *game)
{
	float	start_angle;
	float	angle;
	int		ray_n;
	t_ray	ray;
	float	dist[960];

	start_angle = game->map.theta - ANGLE / 2;
	ray_n = -1;
	while (++ray_n < SCREEN_X)
	{
		angle = start_angle + (ray_n + 1) * ANGLE / SCREEN_X;
		//game->camera.camera_x = ray_n / (double) 920;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		ray = digital_differential_analyzer(&game->map, angle);
		dist[ray_n] = ray.dist;
		draw_ray(game, &ray, ray_n, angle);
	}
	draw_sprite(game, (float *) dist, game->texture.sprite);
}

int	draw(t_game *game)
{
	move(game);
	if (game->hook.re)
	{
		paint_background(game);
		draw_by_ray(game);
		mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
		if (game->hook.minimap_on % 2)
			draw_minimap(game);
		game->hook.re = false;
	}
	return (0);
}
