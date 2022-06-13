/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:57:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/13 21:32:22 by min-kang         ###   ########.fr       */
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

void	draw_text(t_game *game, int h, t_raycast ray, int x)
{
	float	fract;
	float	i;
	int		start;
	int     tmp = h;
	t_img	img;

	img = game->texture.wall_n;
	if (game->height > 600)
		h = h / ray.dist;
	i = 0;
	double lol;
	if (modf(ray.wall.x, &lol) == 0)
		fract = modf(ray.wall.y, &lol);
	else
		fract = modf(ray.wall.x, &lol);
	
	start = 0;
	if (game->height < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;

}

	unsigned int	color;
	float			step;
	int				y;
	
	
void	draw_text(t_game *game, t_img img)
{	
	step = 64.0f / (float) h;
	y = (600 - h) / 2;
    if (y < 0)
	  	y = 0;

	t_point			tex;
	float			tex_pos;
	unsigned int	color;
	int				i;

	tex.x = fract * 64;
	tex.y = 0;
	tex_pos = (draw_start - (600 + h) / 2) * step;
	i = 0;
	while (i++ < tmp)
	{
		tex.y = (int) tex_pos & (64 - 1);
		tex_pos += step;
		color = get_data_color(tex.x, tex.y, img.addr, img);
		my_mlx_pixel_put(&game->gui, x, start + i, color);
	}
}