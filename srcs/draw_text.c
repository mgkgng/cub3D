#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

// Comment recuperer la texture.

t_text	*t_init(void)
{
	t_text *temp;

	temp = malloc(sizeof(t_text));
	temp->w = 32;
	temp->h = 32;
	return (temp);
}

unsigned int	get_data_color(int x, int y, void *addr, t_text *p)
{
	char	*dst;

	dst = addr + (y * p->line_length + x * (p->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int		get_column(int	x, int width)
{
	float c;

	c = x * width;
	return ((int)c);
}

// void	draw_text(t_drawed *d)
// {
// 	// float	y;
// 	// (void)game;
// 	// int		start;
// 	// int     tmp = h;

// 	if (d->game->height > 600)
// 		d->h = (int) d->h / d->ray.dist;
// 	if (d->ray.wall.x - (int)d->ray.wall.x == 0)
// 		d->y = d->ray.wall.y - (int)d->ray.wall.y;
// 	else
// 		d->y = d->ray.wall.x - (int)d->ray.wall.x; // On recuperer le bon endroit ou ca a frappe;
// 	if (d->game->height < SCREEN_Y)
// 		d->start = (int)((SCREEN_Y - d->h) / 2);
// 	// unsigned int color = 0;
// 	d->step = (double) 64 / (double) d->h;
// 	//Draw utilisation
// 	d->drawstart = -d->h / 2 + 600 / 2;
//     if (d->drawstart < 0)
// 	  	d->drawstart = 0;
//     d->drawend = d->h / 2 + 600 / 2;
//     if(d->drawend >= d->h)
// 		d->drawend = d->h - 1;
// 	d->texpos = (d->drawstart - 600 / 2 + d->h / 2) * d->step;
// 	// Draw end of utilisation
// 	// int	texx;
// 	d->texx = (int)(d->y * (double)64);
// 	// double texy = 0;
// 	int j = 0;
// 	while (j++ < d->tmp)
// 	{
// 		d->texy = (int)d->texpos & (64 - 1);
// 		d->texpos += d->step;
// 		d->color = get_data_color((int) d->texx, d->texy, d->text);
// 		my_mlx_pixel_put(&d->game->gui, d->ray_x, d->start + j , d->color);
// 	}
// }

int	is_door(t_point *door, int x, int y, t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->nb_door)
		if (door[i].x == x && door[i].y == y)
			return (1);
	return (0);
}

void	fdraw_text(t_game *game, int h, t_raycast ray, int ray_x, t_text *t)
{
	float	y;
	float	i;
	(void)game;
	int		start;
	int     tmp = h;
	void	*img_addr;

	if (is_door(game->map.door, (int) ray.wall.x, (int) ray.wall.y, game))
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
	double	step = (double) 64 / (double) h;
	int drawStart = (600 - h) / 2;
    if (drawStart < 0)
	  	drawStart = 0;
    int drawEnd = (h + 600) / 2;
    if(drawEnd >= h)
		drawEnd = h - 1;
	int	texx;
	texx = (int)(y * (double)64);
	double texPos = (drawStart - 600 / 2 + h / 2) * step;
	double texy = 0;
	while (j++ < tmp)
	{
		texy = (int)texPos & (64 - 1);
		texPos += step;
		color = get_data_color((int) texx, texy, img_addr, t);
		my_mlx_pixel_put(&game->gui, ray_x, start + j , color);
	}
}