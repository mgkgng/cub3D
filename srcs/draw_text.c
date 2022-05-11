#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

// Comment recuperer la texture.

t_text	*t_init(void)
{
	t_text *temp;

	temp = malloc(sizeof(t_text));
	temp->img = NULL;
	temp->addr = NULL;
	temp->mlx = NULL;
	temp->bits_per_pixel = 0;
	temp->endian = 0;
	temp->line_length = 0;
	temp->w = 32;
	temp->h = 32;
	return (temp);
}

void	draw_text(t_game *game, int h, int x, t_raycast ray)
{
	// Essaye avec une texture partout
	// int	startY;
	// int	line; // C'est la ligne de l'image qu'on doit afficher;
	t_text *t;

	t = t_init();
	t->img = mlx_xpm_file_to_image(game->gui.mlx, "../texture/test.xpm", t->w, t->h);
	t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length, &t->endian);

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
	/*
		Probleme : Recupere la ligne de l'image.
	*/
}
