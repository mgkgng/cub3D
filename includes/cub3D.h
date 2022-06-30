/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 21:35:22 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# include "libft.h"
# include "texture.h"
# include "key.h"
# include "sprite.h"
# include "draw.h"
# include "utils.h"

# define PI 3.141592
# define DEG 0.017453
# define ANGLE 1.15192f

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

typedef struct s_ray
{
	t_point	wall;
	float	dist;
	int		side[2];
	int		wall_side;
	t_list	*object;
}	t_ray;

typedef struct s_game
{
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
t_img			which_texture(t_ray ray, t_map *map, t_texture *text, float angle);
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

/* sprite */
void			draw_sprite(t_game *game, t_map *map, float *dist, t_img img);
void			begin_thread(t_game *game);

/* utils */
int				terminate(t_game *game);

#endif
