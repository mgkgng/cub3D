#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

// Comment recuperer la texture.

t_text	*t_init(void)
{
	t_text *temp;

	temp = malloc(sizeof(t_text));
	temp->w = 64;
	temp->h = 64;
	return (temp);
}

unsigned int	get_data_color(int x, int y, void *addr, t_text *p)
{
	char	*dst;

	dst = addr + (y * p->line_length + x * (p->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	is_door(t_point *door, int x, int y, t_game *game)
{
	int	i;

	i = -1;
	// printf("COUNT : %i\n", game->nb_count);
	int side_x = 0;
	int side_y = 0;

	if (game->map.theta > PI && game->map.theta < PI * 2)
		side_y--;
	if (game->map.theta > PI / 2 && game->map.theta < PI / 2 * 3)
		side_x--;
	while (++i <= game->nb_count) {

		// printf("X : %f\n Y : %f\n", door[i].x, door[i].y);
		if (door[i].x == x && door[i].y == y)
			return (1);
		// else if (door[i].x + side_x == x && door[i].y == y)
		// 	return (1);
		// else if (door[i].x + side_x == x && door[i].y + side_y == y)
		// 	return (1);
	}
	return (0);
}

void	draw_text(t_game *game, int h, t_raycast ray, int ray_x, t_text *t)
{
	float	y;
	float	i;
	// (void)game;
	int		start;
	int     tmp = h;
	void	*img_addr;

	int side_x = 0;
	int side_y = 0;

	if (game->map.theta > PI && game->map.theta < PI * 2)
		side_y--;
	if (game->map.theta > PI / 2 && game->map.theta < PI / 2 * 3)
		side_x--;
	if (game->mapi[(int) ray.wall.y][(int) ray.wall.x] == '2')
		img_addr = game->t->addr_door;
	else if (is_door(game->door, (int) ray.wall.x + side_y, (int) ray.wall.y + side_x, game))
		img_addr = game->t->addr_door;
	else
		img_addr = game->t->addr_wall;
	if (game->height > 600)
		h = (int) h / ray.dist;
	start = 0;
	i = 0;
	if (ray.wall.x - (int)ray.wall.x == 0)
		y = ray.wall.y - (int)ray.wall.y;
	else
		y = ray.wall.x - (int)ray.wall.x; // On recuperer le bon endroit ou ca a frappe;
	if (game->height < SCREEN_Y)
		start = (int)((SCREEN_Y - h) / 2);
	int j = 0;
	unsigned int color = 0;
	float	step = (float) 64 / (float) h;
	int drawStart = -h / 2 + 600 / 2;
    if (drawStart < 0)
	  	drawStart = 0;
    int drawEnd = h / 2 + 600 / 2;
    if(drawEnd >= h)
		drawEnd = h - 1;
	int	texx;
	texx = (int)(y * (float)64);
	float texPos = (drawStart - 600 / 2 + h / 2) * step;
	float texy = 0;
	while (j++ < tmp)
	{
		texy = (int)texPos & (64 - 1);
		texPos += step;
		color = get_data_color((int) texx, texy, img_addr, t);
		my_mlx_pixel_put(&game->gui, ray_x, start + j , color);
	}
}

