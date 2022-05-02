#include "cub3D.h"

// int	wich_texture(t_game *game, t_raycast ray)
// {

// }

char	**get_texture(int fd)
{
	char	*line;
	int		ret;
	char	buf[2];

	ret = read(fd, buf, 2);
	buf[ret] = '\0';
	line = ft_strdup(buf);
	while (ret > 0)
	{
		ret = read(fd, buf, 2);
		buf[ret] = '\0';
		line = ft_strjoin(line, buf);
		// free line dans strjoin
	}
	return (ft_split(line, '\n'));
}

void	draw_text(t_game *game, int h, int x, t_raycast ray)
{
	// Essaye avec une texture partout
	int	startY;
	int	line; // C'est la ligne de l'image qu'on doit afficher;

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
