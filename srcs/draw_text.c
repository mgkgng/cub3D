/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:57:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 19:06:58 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	get_height(float dist, t_game *game)
{
	int		h;

	h = SCREEN_Y / dist;
	if (h > SCREEN_Y)
	{
		game->height = h;
		h = SCREEN_Y;
	}
	else
		game->height = h;
	return (h);
}

unsigned int	get_data_color(int x, int y, void *addr, t_img img)
{
	char	*dst;

	dst = addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_tex_info	get_tex_info(t_point wall, int h, int start)
{
	t_tex_info	info;

	if (wall.x - (int) wall.x == 0)
		info.fract = wall.y - (int) wall.y;
	else
		info.fract = wall.x - (int) wall.x;
	info.step = 64.0f / (float) h;
	info.x = info.fract * 64;
	(void) start;
	info.tex_pos = (start - (600 - h + 1) / 2) * info.step;
	return (info);
}

t_img	which_texture(int wall_side, t_texture *text, float angle)
{
	if (wall_side == 1)
	{
		if (angle <= 3 * PI / 2 && angle >= PI / 2)
			return (text->wall_w);
		return (text->wall_e);
	}
	else
	{
		if (angle > PI && angle < 2 * PI)
			return (text->wall_n);
		return (text->wall_s);
	}
}

void	draw_wall(t_game *game, t_ray ray, int ray_n, float angle)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info 		info;
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

void	draw_object(t_game *game, t_list *obj, int ray_n)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info 		info;
	int				i;
	
	h = get_height(obj->dist, game);
	if (game->height > 600)
		h = h / obj->dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(obj->pos, h, start);
	if (obj->type == DOOR)
		info.img = game->texture.door;
	else
		info.img = game->texture.sprite;
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		put_pixel(&game->screen, ray_n, start + i, color);
	}
}

void	draw_img(t_game *game, t_ray *ray, int ray_x, float angle)
{
	t_list	*current_obj;
	
	draw_wall(game, *ray, ray_x, angle);
	current_obj = ray->object;
	while (current_obj)
	{
		draw_object(game, current_obj, ray_x);
		current_obj = current_obj->next;
	}
	free_list(ray->object);
}
