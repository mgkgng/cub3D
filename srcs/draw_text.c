#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

// Comment recuperer la texture.

t_text	*t_init(void)
{
	t_text *temp;

	temp = malloc(sizeof(t_text));
	// temp->img = NULL;
	// temp->addr = NULL;
	// temp->mlx = NULL;
	// temp->bits_per_pixel = 0;
	// temp->endian = 0;
	// temp->line_length = 0;
	temp->w = 32;
	temp->h = 32;
	return (temp);
}

unsigned int	get_data_color(int x, int y, t_text *p)
{
	char	*dst;

	dst = p->addr + (y * p->line_length + x * (p->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int		get_column(int	x, int width)
{
	float c;

	c = x * width;
	return ((int)c);
}

void	draw_text(t_game *game, int h, t_raycast ray, int ray_x, t_text *t)
{
	float	y;
	float	i;
	(void)game;
	int		start;
	int     tmp = h;

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
	int drawStart = -h / 2 + 600 / 2;
    if (drawStart < 0)
	  	drawStart = 0;
    int drawEnd = h / 2 + 600 / 2;
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
		color = get_data_color((int) texx, texy, t);
		my_mlx_pixel_put(&game->gui, ray_x, start + j , color);
	}
}

