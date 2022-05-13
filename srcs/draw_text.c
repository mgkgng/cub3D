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
	// Essaye avec une texture partout
	// int	startY;
	// int	line; // C'est la ligne de l'image qu'on doit afficher;
	// t_text 			*t;
	// int				i;
	// unsigned int	color;
	float	y;
	float	i;
	(void)game;
	int		start;
	int     tmp = h;
	// (void)h;

	if (game->height > 600)
		h = (int) h / ray.dist;
	start = 0;
	i = 0;
	if (ray.wall.x - (int)ray.wall.x == 0)
	{
		// printf("%f\n", ray.wall.y); // Prendre le reste
		y = ray.wall.y - (int)ray.wall.y;
	}
	else
	{
		// printf("%f\n", ray.wall.x);
		y = ray.wall.x - (int)ray.wall.x; // On recuperer le bon endroit ou ca a frappe;
	}
	// 	y = La colonne a prendre sur la texture;
	// 	Maintenant il faut boucler pour avoir le x 
	//	donc l'index de la collone qui correspond au pixel qu'il faut.
	// printf("La collone %f\n", y);
	// Comment faire pour scale ?
	// printf("Height %i\n", h);
	// printf("HEIGHT %i\n", game->height);
	if (game->height > SCREEN_Y)
	{
		while (game->height > SCREEN_Y)
		{
			i += 64 / h;
			game->height--;
		}
	}
	else
	{
		start = (int)((SCREEN_Y - h) / 2);
	}
	// printf("Saut de pixel : %i\n", i);
	// printf("Start : %i\n", start);
	int j = 0;
	unsigned int color = 0;
	// printf("I %i\n", h);
	//calculate value of wallX
    //   double wallX; //where exactly the wall was hit
    //   if (side == 0) wallX = posY + perpWallDist * rayDirY;
    //   else           wallX = posX + perpWallDist * rayDirX;
    //   wallX -= floor((wallX));
	double	step = (double) 64 / (double) h;
	int drawStart = -h / 2 + 600 / 2;
    if (drawStart < 0)
	  	drawStart = 0;
    int drawEnd = h / 2 + 600 / 2;
    if(drawEnd >= h)
		drawEnd = h - 1;
	int	texx;
	// double wallX;
	texx = (int)(y * (double)64);
    // texx = 32 - texx - 1;
	double texPos = (drawStart - 600 / 2 + h / 2) * step;
	// printf("%i\n", drawStart);
	// printf("%f\n", texPos);
	// printf("Texpos : %f\n", texPos);
	double texy = 0;
	// pos = (h / 2) - (600 / 2) * ((double) 32 / (double) h);
	while (j++ < tmp)
	{
		// ty = (int)index & (64 - 1);
		texy = (int)texPos & (64 - 1);
		texPos += step;
		color = get_data_color((int) texx, texy, t);
		my_mlx_pixel_put(&game->gui, ray_x, start + j , color);
		// Faire la propotionnalite, c'est index.
	}
}
/*
	i = 0; // L'index du pixel a afficher;
	t = t_init();
	t->img = mlx_xpm_file_to_image(game->gui.mlx, "../texture/test.xpm", t->w, t->h);
	t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);
	while (i < h)
	{
		color = get_data_color(x, y, t);
	}
	// printf("%c\n", img[0]);
	// line = (int) ray.wall.x;
	// line = line * // Longueur longeur de l'image;
	// startY = (int) ((SCREEN_Y - h) /2);
	// Il faut trouver le line_start (h)
	// Le debut de la ou il faut commencer a dessiner la ligne dans la fenetre.
	// i - line_start = position de la ou il faut dessiner. (K)
	// line_end - line_start = longueur de la ligne. (L)
	// (K / L) * texture_hauteur = le pixel qui faut afficher.
	// (h = LIGNE START)
	
		Probleme : Recupere la ligne de l'image.
	*/

