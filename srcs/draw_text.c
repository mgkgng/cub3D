/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:57:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/11 19:36:31 by min-kang         ###   ########.fr       */
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

static bool	is_door(t_point *door, int x, int y, int nb)
{
	int	i;

	i = -1;
	while (++i <= nb)
		if (door[i].x == x && door[i].y == y)
			return (true);
	return (false);
}

void	draw_text(t_game *game, t_map map, int h, t_raycast ray, int ray_n, t_texture texture)
{
	float	y;
	float	i;
	int		start;
	int     tmp = h;
	t_img	img;

	if (is_door(map.doors, (int) ray.wall.x + ray.side[0], (int) ray.wall.y + ray.side[1], map.doors_nb))
		img = texture.door;
	else
		img = texture.wall_n;
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

