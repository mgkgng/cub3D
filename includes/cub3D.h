/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/03 23:37:03 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>

#include "libft.h"
#include "hook.h"
#include "raycast.h"

#define	PI 3.141592
#define DEG	0.017453

#define	BLOCKSIZE 18
#define MINI_X 20
#define MINI_Y 20
#define MINI_W 150
#define MINI_H 150
#define	SCREEN_X 920
#define SCREEN_Y 600

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

typedef struct s_draw {
	char	*nswe[4];
	int		col_floor;
	int		col_ceil;
}	t_draw;

typedef struct s_map {
	int		width;
	int		height;
	bool	**map2d;
	t_point	pos;
	t_point pixel_pos;
	double	theta;
}	t_map;

typedef struct s_gui {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	//* bonus
	void	*mini_img;
	char	*mini_addr;
	int		mini_pixel;
	int		mini_len;
	int		mini_endian;
	//* bonus
	int		bits_per_pixel;
	int		line_len;
	int		endian;
} 	t_gui;

typedef struct s_hook {
	bool	re;
	//*bonus
	bool	minimap_on;
	int		x_prev;
	int		m_turn;
	int		m_dir;
	int		m_sensibility;
}	t_hook;

typedef struct s_game {
	t_map	map;
	t_gui	gui;
	t_hook	hook;
	t_draw	draw;
}	t_game;

typedef struct	s_raycast {
	t_point	wall;
	double	dist;
}	t_raycast;

int	cub3D(t_game game);
//int	cub3D(void);

/* parse */
t_game	parse(char *file);

/* error */
void	error(int c);

void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color);

void	draw_cub3D(t_game *game);

int		key_hook(int key, t_game *game);

int		terminate(t_game *game);
t_raycast	digital_differential_analyzer(t_map map, double theta);

/*parse utils*/
int		check_filename(char *file);
int		check_fileformat(char *mapstr, char **map);
int		get_color(char *colstr);

//*bonus

void	draw_minimap(t_game *game);
void	minimap_pixel_put(t_gui *gui, int x, int y, int color);
int		mouse_hook(int x, int y, t_hook *hook);


void	turn(t_map *map, int dir);

#endif