/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:57:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/14 16:43:09 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	draw_text(t_game *game, t_img img, float dist, t_point touch, int ray_x)
{
	int	h;
	int	start_y;
	int	i;
	t_tex_info	tex_info;

	h = SCREEN_Y / dist;
	start_y = (SCREEN_Y - h) / 2;
	if (start_y < 0)
		start_y = 0;
	if (h > SCREEN_Y)
		h = h / dist;
	tex_info = get_tex_info(touch, h, start_y);
	i = 0;
	while (i++ < h)
	{
		tex_info.tex.y = (int) tex_info.tex_pos & (64 - 1);
		my_mlx_pixel_put(&game->gui, ray_x, start_y + i, get_data_color(tex_info.tex.x, tex_info.tex.y, img.addr, img));
		tex_info.tex_pos += tex_info.step;
	}
}

void	draw_img(t_game *game, t_raycast ray, int ray_x)
{
	draw_text(game, game->texture.wall_n, ray.dist, ray.wall, ray_x);
	/*while (ray.door.nb--)
		draw_text(game, game->texture.door, ray.door.dist[ray.door.nb], ray.door.pos[ray.door.nb], ray_x);*/
}