/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:57:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 04:54:14 by min-kang         ###   ########.fr       */
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

t_texture	get_texture_img(t_draw draw, void *mlx_ptr)
{
	t_texture	res;
	int			size_info[2];

	
	res.wall_n.img = mlx_xpm_file_to_image(mlx_ptr, draw.nswe[0], &size_info[0], &size_info[1]);
	res.wall_s.img = mlx_xpm_file_to_image(mlx_ptr, draw.nswe[1], &size_info[0], &size_info[1]);
	res.wall_w.img = mlx_xpm_file_to_image(mlx_ptr, draw.nswe[2], &size_info[0], &size_info[1]);
	res.wall_e.img = mlx_xpm_file_to_image(mlx_ptr, draw.nswe[3], &size_info[0], &size_info[1]);
	res.door.img = mlx_xpm_file_to_image(mlx_ptr, "./texture/Door_final.xpm", &size_info[0], &size_info[1]);
	res.wall_n.addr = mlx_get_data_addr(res.wall_n.img, &res.wall_n.bits_per_pixel, &res.wall_n.line_length, &res.wall_n.endian);
	res.wall_s.addr = mlx_get_data_addr(res.wall_s.img, &res.wall_s.bits_per_pixel, &res.wall_s.line_length, &res.wall_s.endian);
	res.wall_w.addr = mlx_get_data_addr(res.wall_w.img, &res.wall_w.bits_per_pixel, &res.wall_w.line_length, &res.wall_w.endian);
	res.wall_e.addr = mlx_get_data_addr(res.wall_e.img, &res.wall_e.bits_per_pixel, &res.wall_e.line_length, &res.wall_e.endian);
	res.door.addr = mlx_get_data_addr(res.door.img, &res.door.bits_per_pixel, &res.door.line_length, &res.door.endian);
	return (res);
}

unsigned int	get_data_color(int x, int y, void *addr, t_img img)
{
	char	*dst;

	//printf("%zu...%d...%d...\n", ft_strlen((char *)addr), y * img.line_length, x * (img.bits_per_pixel / 8));
	dst = addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	//printf("%p.....\n", dst);
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
	info.tex_pos = (start - (600 + h) / 2) * info.step;
	return (info);
}

t_img which_texture(t_game *g, t_texture text, float angle)
{
	// printf("%f\n", g->map.theta);
	if (g->side == 1)
	{
		if (angle <= 3 * PI / 2 && angle >= PI / 2)
			return (text.wall_w);
		return (text.wall_e);
	}
	else
	{
		if (angle > PI && angle < 2 * PI)
			return (text.wall_n);
		return (text.wall_s);
	}
}

void	draw_text(t_game *game, t_raycast ray, int ray_n, float angle)
{
	int		start;
	int		h;
	unsigned int color;
	t_tex_info info;
	int	i;
	
    h = get_height(ray.dist, game);
	if (game->height > 600)
		h = h / ray.dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(ray.wall, h, start);
	info.img = which_texture(game, game->texture, angle);
	// printf("%s\n", info.img.addr);
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		my_mlx_pixel_put(&game->gui, ray_n, start + i, color);
	}
}

void	draw_door(t_game *game, float dist, t_point wall, int ray_n)
{
	int		start;
	int		h;
	unsigned int color;
	t_tex_info info;
	int	i;
	t_img	img;
	
	img = game->texture.door;
	h = get_height(dist, game);
	if (game->height > 600)
		h = h / dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(wall, h, start);
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, img.addr, img);
		my_mlx_pixel_put(&game->gui, ray_n, start + i, color);
	}	
}

void	draw_img(t_game *game, t_raycast ray, int ray_x, float angle)
{
	t_door	*door_now;
	draw_text(game, ray, ray_x, angle);

	door_now = ray.door;
	printf("-----%p----\n", &door_now);
	while (door_now)
	{
		draw_door(game, door_now->dist, door_now->pos, ray_x);
		door_now = door_now->next;
	}
	printf("-----%p----\n", &ray.door);
	free_lst(ray.door);
}