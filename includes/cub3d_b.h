/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:25:16 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:50:19 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_B_H
# define CUB3D_B_H

# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>

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

typedef struct s_list {
	t_point			pos;
	t_point			map_pos;
	float			dist;
	struct s_list	*next;
}	t_list;

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
	t_img	door_o;
	t_img	door_c;
	t_img	spr[7];
	int		spr_now;
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

typedef struct s_camera {
	float	plane_x;
	float	plane_y;
	float	dir_x;
	float	dir_y;
}	t_camera;

typedef struct s_sprite {
	float	x;
	float	y;
	float	c;
	float	x_trans;
	float	y_trans;
	float	x_screen;
	float	w;
	float	h;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
}	t_sprite;

typedef enum e_key {
	KEY_ESC = 53,
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	KEY_TURN_L = 123,
	KEY_TURN_R = 124,
	KEY_MINI = 46,
	KEY_DOOR = 14
}	t_key;

typedef enum e_pressed {
	UP = 1 << 0,
	DOWN = 1 << 1,
	LEFT = 1 << 2,
	RIGHT = 1 << 3,
	TURN_L = 1 << 4,
	TURN_R = 1 << 5,
	MOUSE_L = 1 << 6,
	MOUSE_R = 1 << 7,
}	t_pressed;

typedef struct s_hook {
	bool			re;
	int				flag;
	unsigned int	minimap_on;
	unsigned int	minimap_size;
	int				mouse_x_prev;
}	t_hook;

typedef struct s_map {
	int			width;
	int			height;
	bool		**map_move;
	char		**map_wall;
	t_point		pos;
	t_point		*spr;
	int			spr_nb;
	float		theta;
	t_camera	camera;
}	t_map;

typedef struct s_ray {
	t_point	wall;
	float	dist;
	int		side[2];
	int		wall_side;
	t_list	*object;
}	t_ray;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		screen;
	t_img		minimap;
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

/* key */
int				key_pressed(int key, t_game *game);
int				key_released(int key, t_game *game);
void			move(t_game *game);
void			translate(t_map *map, float theta);

/* dda */
t_ray			digital_differential_analyzer(t_map *map, float theta);
t_dda			init_dda(float theta, int xy);
bool			is_through(t_map *map, int x, int y);
void			is_object(t_ray *ray, t_map *map, int *pos);
float			perpendicular_dist(t_point from, t_point to, float angle);

/* draw */
int				draw(t_game *game);
float			get_height(float dist, t_game *game);
unsigned int	get_data_color(int x, int y, void *addr, t_img img);
t_tex_info		get_tex_info(t_point wall, int h, int start);
t_img			which_texture(t_ray ray, t_map *map,
					t_texture *text, float angle);
void			paint_background(t_game *game);

/* list */
t_list			*ft_lstnew(t_point pos, float dist, t_point map_pos);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			free_list(t_list *lst);
void			manip_list(t_list **one, t_list *other);
t_list			*copy_list(t_list *lst);
void			combine_list(float dist, t_list **origin, t_list *compare);

/* bonus */
void			init_bonus(t_game *game);

/* sprite */
float			get_sprite_dist(t_point ray_p, float dist, float theta);
void			get_sprite(t_map *map, char **charmap);

/* mouse */
int				mouse_hook(int x, int y, t_game *game);

/* door */
void			open_door(t_game *game);
void			free_chartab(char **tab);

/* minimap */
void			draw_minimap(t_game *game);
void			fill_floor(t_game *game, int size, int color);

/* sprite */
void			draw_sprite(t_game *game, t_map *map, float *dist, t_img img);
void			begin_thread(t_game *game);

/* utils */
int				terminate(t_game *game);

#endif
