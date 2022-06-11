#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

// Comment recuperer la texture.

t_texture	*get_texture(t_game game)
{
	t_texture	res;

	res.width = 64;
	res.height = 64;
	res.img_wall = mlx_xpm_file_to_image(game.gui.mlx, "./texture/wall.xpm", &game.texture.width, &game.texture.height);
	res.img_door = mlx_xpm_file_to_image(game.gui.mlx, "./texture/Group-2.xpm", &game.texture.width, &game.texture.height);
	res.addr_wall = mlx_get_data_addr(game.texture.img_wall, &game.texture.bits_per_pixel, &game.texture.line_length, &game.texture.endian);
	res.addr_door = mlx_get_data_addr(game.texture.img_door, &game.texture.bits_per_pixel, &game.texture.line_length, &game.texture.endian);
	return (res);
}

unsigned int	get_data_color(int x, int y, void *addr, t_texture *p)
{
	char	*dst;

	dst = addr + (y * p->line_length + x * (p->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

bool	is_door(t_point *door, int x, int y, int nb)
{
	int	i;

	i = -1;
	while (++i <= nb)
		if (door[i].x == x && door[i].y == y)
			return (true);
	return (false);
}

void	draw_text(t_game *game, int h, t_raycast ray, int ray_n, t_texture t)
{
	float	y;
	float	i;
	// (void)game;
	int		start;
	int     tmp = h;
	void	*img_addr;

	if (game->mapi[(int) ray.wall.y + ray.side[1]][(int) ray.wall.x + ray.side[0]] == '2')
		img_addr = t.addr_door;
	else if (is_door(game->map.doors, (int) ray.wall.x + ray.side[0], (int) ray.wall.y + ray.side[1], game->map.doors_nb))
		img_addr = t.addr_door;
	else
		img_addr = game->t->addr_wall;
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
		color = get_data_color((int) texx, texy, img_addr, t);
		my_mlx_pixel_put(&game->gui, ray_x, start + j , color);
	}
}

