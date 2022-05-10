#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

// Comment recuperer la texture.

void	draw_text(t_game *game, int h, int x, t_raycast ray)
{
	// Essaye avec une texture partout
	// int	startY;
	// int	line; // C'est la ligne de l'image qu'on doit afficher;
	void	*img;
	void	*mlx;
	int	i;

	i = 0;
	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, "../texture/test.xpm", 32, 32);
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
