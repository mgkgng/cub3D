/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:57:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/14 22:53:25 by min-kang         ###   ########.fr       */
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


t_texture	get_texture(void *mlx_ptr) // it should be developped as we start to want to put more images
// there will be another parameter later, the path infos for each texture
{
	t_texture	res;
	int			size_info[2];

	res.wall_n.img = mlx_xpm_file_to_image(mlx_ptr, "./texture/wall.xpm", &size_info[0], &size_info[1]);
	res.door.img = mlx_xpm_file_to_image(mlx_ptr, "./texture/Group-2.xpm", &size_info[0], &size_info[1]);
	res.wall_n.addr = mlx_get_data_addr(res.wall_n.img, &res.wall_n.bits_per_pixel, &res.wall_n.line_length, &res.wall_n.endian);
	res.door.addr = mlx_get_data_addr(res.door.img, &res.door.bits_per_pixel, &res.door.line_length, &res.door.endian);
	return (res);
}

unsigned int	get_data_color(int x, int y, void *addr, t_img img)
{
	char	*dst;

	dst = addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

/*unsigned int	get_data_color(t_point p, t_img img, void *addr)
{
	char	*dst;

	dst = addr + (p.y * img.line_length + p.x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}*/

t_tex_info	get_tex_info(t_point touch, int h, int start_y)
{
	t_tex_info	res;

	if (touch.x - (int) touch.x == 0)
		res.fract = touch.y - (int) touch.y;
	else
		res.fract = touch.x - (int) touch.x;
	res.step = 64.0f / (float) h;
	res.tex.x = res.fract * 64;
	res.tex_pos = (start_y - (600 + h) / 2) * res.step;
	return (res);
}

/*void	draw_text(t_game *game, t_img img, float dist, t_point touch, int ray_x)
{
	int	h;
	int	start_y;
	int	i;
	int	tmp;
	t_tex_info	tex_info;

	h = get_height(dist, game);
	tmp = h;
	start_y = (SCREEN_Y - h) / 2;
	if (start_y < 0)
		start_y = 0;
	if (h > SCREEN_Y)
		h = h / dist;
	tex_info = get_tex_info(touch, h, start_y);
	i = -1;
	while (++i < tmp)
	{
		tex_info.tex.y = (int) tex_info.tex_pos & (64 - 1);
		my_mlx_pixel_put(&game->gui, ray_x, start_y + i, get_data_color(tex_info.tex.x, tex_info.tex.y, img.addr, img));
		tex_info.tex_pos += tex_info.step;
	}
}*/

void	draw_text(t_game *game, t_img img, int h, t_raycast ray, int ray_n)
{
	float	y;
	float	i;
	int		start;
	int     tmp = h;

	if (game->height > 600)
		h = h / ray.dist;
	start = 0;
	i = 0;
	double lol;
	if (modf(ray.wall.x, &lol) == 0)
		y = modf(ray.wall.y, &lol);
	else
		y = modf(ray.wall.x, &lol); // On recuperer le bon endroit ou ca a frappe;
	if (game->height < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	int j = 0;
	unsigned int color = 0;
	float	step = 64.0f / (float) h;
	int drawStart = (600 - h) / 2;
    if (drawStart < 0)
	  	drawStart = 0;
    int drawEnd = (600 + h) / 2;
    if(drawEnd >= h)
		drawEnd = h - 1;
	int	texx;
	texx = y * 64;
	float texPos = (drawStart - (600 + h) / 2) * step;
	float texy = 0;
	while (j++ < tmp)
	{
		texy = (int) texPos & (64 - 1);
		texPos += step;
		color = get_data_color((int) texx, texy, img.addr, img);
		my_mlx_pixel_put(&game->gui, ray_n, start + j , color);
	}
}

void	draw_img(t_game *game, t_raycast ray, int ray_x)
{
	draw_text(game, game->texture.wall_n, get_height(ray.dist, game), ray, ray_x);
	/*while (ray.door.nb--)
		draw_text(game, game->texture.door, ray.door.dist[ray.door.nb], ray.door.pos[ray.door.nb], ray_x);*/
}