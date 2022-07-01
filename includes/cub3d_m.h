/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_m.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/07/01 10:38:58 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_M_H
# define CUB3D_M_H

# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# include "libft.h"

# define PI 3.141592
# define DEG 0.017453
# define ANGLE 1.15192f

# define IMG_WIDTH 64
# define IMG_HEIGHT 64

# define BLOCKSIZE 18
# define MINI_X 20
# define MINI_Y 20
# define MINI_SQUARE 50
# define MINI_W 250
# define MINI_H 250
# define SCREEN_X 920
# define SCREEN_Y 600

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

typedef struct s_draw {
	char	**nswe;
	int		col_floor;
	int		col_ceil;
}	t_draw;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture {
	t_img	wall_n;
	t_img	wall_s;
	t_img	wall_w;
	t_img	wall_e;
}	t_texture;

typedef struct s_tex_info {
	int		x;
	int		y;
	float	tex_pos;
	float	fract;
	float	step;
	t_img	img;
}	t_tex_info;

typedef struct s_dda {
	float	delta;
	int		incre;
	int		side;
}	t_dda;

typedef enum e_key {
	KEY_ESC = 53,
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	KEY_TURN_L = 123,
	KEY_TURN_R = 124,
}	t_key;

typedef enum e_pressed {
	UP = 1 << 0,
	DOWN = 1 << 1,
	LEFT = 1 << 2,
	RIGHT = 1 << 3,
	TURN_L = 1 << 4,
	TURN_R = 1 << 5,
}	t_pressed;

typedef struct s_hook {
	bool			re;
	int				flag;
}	t_hook;

typedef struct s_map {
	int			width;
	int			height;
	bool		**map_move;
	char		**map_wall;
	t_point		pos;
	float		theta;
}	t_map;

typedef struct s_ray {
	t_point	wall;
	float	dist;
	int		side[2];
	int		wall_side;
}	t_ray;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		screen;
	t_hook		hook;
	t_draw		draw;
	int			height;
	t_texture	texture;
}	t_game;

/* cub3d */
int				cub3d(t_game game);

/* parse */
t_game			parse(char *filename);
t_map			get_map(char **lines);
t_draw			get_draw(char **lines);
char			**get_lines(int fd);
int				get_fd(char *filename);
int				ft_tablen(char **map);
int				check_filename(char *file);
int				verif_texture(char *dir);
void			check_map_horizontal(char **map);
void			check_map_vertical(t_map *map);
int				check_filename(char *file);
int				check_texture(char *dir);
void			check_lines(char *line);

/* utils */
void			end_program(char *str, int tag);
void			put_pixel(t_img *img, int x, int y, int color);
int				terminate(t_game *game);
void			free_chartab(char **tab);

/* key */
int				key_pressed(int key, t_game *game);
int				key_released(int key, t_game *game);
void			move(t_game *game);
void			translate(t_map *map, float theta);

/* dda */
t_ray			digital_differential_analyzer(t_map *map, float theta);
t_dda			init_dda(float theta, int xy);
bool			is_through(t_map *map, int x, int y);
float			perpendicular_dist(t_point from, t_point to, float angle);

/* draw */
int				draw(t_game *game);
float			get_height(float dist, t_game *game);
unsigned int	get_data_color(int x, int y, void *addr, t_img img);
t_tex_info		get_tex_info(t_point wall, int h, int start);
t_img			which_texture(int wall_side, t_texture *text, float angle);
void			paint_background(t_game *game);

#endif
