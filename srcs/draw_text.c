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
	int i;
	(void)game;
	int		start;
	// (void)h;

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
	if (game->height > SCREEN_Y)
	{
		while (game->height > SCREEN_Y)
		{
			i++;
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
	double	index = 0; // Faire en sorte qu'index commence a un certain nombre quand i > 0.
	// printf("Hited %f\n", y * 32);
	while (j++ < h)
	{
		
		color = get_data_color((int) index, y * 32, t);
		my_mlx_pixel_put(&game->gui, ray_x, start + j , color);
		index += (double) 32 / (double) h;
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

