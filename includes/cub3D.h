/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/11 16:52:20 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
// #include <mlx.h>
#include "../minilibx_opengl_20191021/mlx.h"

#include "libft.h"
#include "hook.h"
#include "raycast.h"

#define	PI 3.141592
#define DEG	0.017453

#define	BLOCKSIZE 18
#define MINI_X 20
#define MINI_Y 20
#define MINI_SQUARE 50
#define MINI_W 250
#define MINI_H 250
#define	SCREEN_X 920
#define SCREEN_Y 600

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

typedef enum e_move {
	STOP,
	W,
	S,
	A,
	D
}	t_move;

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
	t_point *door;
	double	theta;
	char	**mapchar;
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
	t_move	move_re;
	//*bonus
	unsigned int	minimap_on;
	unsigned int	minimap_size;
	int		x_prev;
	int		m_turn;
	int		m_dir;
	int		m_sensibility;
	bool	m_re;
}	t_hook;

typedef struct s_text
{
	void	*img_wall;
	void	*img_door;
	char	*addr_wall;
	char	*addr_door;
	void	*mlx;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_text;

typedef struct s_key {
	int	w;
	int	a;
	int	s;
	int	d;
}	t_key;

typedef struct s_game {
	t_map	map;
	t_gui	gui;
	t_hook	hook;
	t_draw	draw;
	t_key	key;
	int		height;
	int		nb_door;
	t_text	*t;
}	t_game;

typedef struct	s_raycast {
	t_point	wall;
	double	dist;
}	t_raycast;

typedef struct s_drawed
{
	unsigned int	color;
	double			step;
	int				drawend;
	int				drawstart;
	double			texpos;
	int				texx;
	double			texy;
	t_game			*game;
	t_raycast		ray;
	int				start;
	t_text			*text;
	int				ray_x;
	float			y;
	int				h;
	int				tmp;
}	t_drawed;

int	cub3D(t_game game);
//int	cub3D(void);

/* parse */
t_game	parse(char *file);

/* error */
void	error(int c);

/* key */
int	key_pressed(int key, t_game game);
int	key_released(int key, t_game game);

void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color);
// int     mlx_mouse_move(mlx_win_list_t *win, int x, int y);
void	draw_cub3D(t_game *game);

int		key_hook(int key, t_game *game);

int		terminate(t_game *game);
t_raycast	digital_differential_analyzer(t_map map, double theta);

/*parse utils*/
int		check_filename(char *file);
int		check_fileformat(char *mapstr, char **map);
int		get_color(char *colstr);
int		is_surrounded(char **map);

//*bonus

void	draw_minimap(t_game *game);
void	minimap_pixel_put(t_gui *gui, int x, int y, int color);
int		mouse_hook(int x, int y, t_hook *hook);

void	turn(t_map *map, int dir);
/*draw*/
void	draw_text(t_drawed *draw);
void	fdraw_text(t_game *game, int h, t_raycast ray, int ray_x, t_text *t);
t_text	*t_init(void);

#endif
