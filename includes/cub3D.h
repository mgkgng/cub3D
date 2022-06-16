/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/16 16:25:15 by mlecherb         ###   ########.fr       */
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
#include "texture.h"

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
	float	x;
	float	y;
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
	t_point *doors;
	int		doors_nb;
	t_point pixel_pos;
	float	theta;
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

typedef struct	s_raycast {
	t_point	wall;
	float	dist;
	int		side[2];
}	t_raycast;

typedef struct s_sprite {
	void	*img;
	char	*addr;
	void	*mlx;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	struct s_sprite *next;
}	t_sprite;

typedef struct	s_key {
	int	w;
	int	a;
	int	s;
	int	d;
	int	turn_l;
	int	turn_r;
}	t_key;

typedef struct s_info {
	int		**rgb;
	char	*path1;
	char	*path2;
	char	*path3;
	char	*path4;
	char	**file;
	char	**text;
	int		i;
	char	**map;
}	t_info;

typedef struct s_dir {
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	camera_x;
	float	raydirx;
	float	raydiry;
}	t_dir;

typedef struct s_game {
	t_dir		dir;
	t_map		map;
	t_gui		gui;
	t_hook		hook;
	t_draw		draw;
	t_raycast	ray;
	t_sprite	*spr;
	t_key		*key;
	t_info		info;
	int			height;
	t_texture	texture;
	int			nb_count;
	float		min_door;
	int			pos[2];
	char		**mapi;
	int			lock;
	int			sprite;
	int 		count;
	int			side;
}	t_game;

int	cub3D(t_game game);
//int	cub3D(void);

/* parse */
t_game	parse(char *file);
char	**get_char_map(char **file, t_info info);
int		**grep_rgb(char **file, t_info info);
char	**grep_texture(char **file, t_info info);
char	**file_to_tab(int fd);
t_info 	parser(char *file);
void	aff_tab(char **map);
int		tab_len(char **map);
void	error_quit(char * msg);
int		verif_texture(char *dir);

/* error */
void	error(int c);

/* key */
int	key_pressed(int key, t_game *game);
int	key_released(int key, t_game *game);
void	movement(t_game *game);
void	translate(t_map *map, float theta);



void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color);

void	draw_cub3D(t_game *game);

int		key_hook(int key, t_game *game);

int		terminate(t_game *game);
// t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game);
t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game, int rayn);
/*parse utils*/
int		check_filename(char *file);
int		check_fileformat(char *mapstr, char **map);
int		get_color(char *colstr);
int		is_surrounded(char **map);

//*bonus

void	draw_minimap(t_game *game);
void	minimap_pixel_put(t_gui *gui, int x, int y, int color);
int		mouse_hook(int x, int y, t_hook *hook);
void	turn(t_game *game, t_map *map, int dir);
/*draw*/
void	draw_text(t_game *game, t_map map, int h, t_raycast ray, int ray_n, float angle);

void	init_dir(t_game *game);
float	perpendicular_dist(float *from, float *to, float angle);

#endif
