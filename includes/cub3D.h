/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/13 17:48:53 by min-kang         ###   ########.fr       */
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

#define	BLOCKSIZE 18
#define MINIMAP_X 100
#define MINIMAP_Y 100

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
	int		game_width;
	int		game_height;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
} 	t_gui;

typedef struct s_hook {
	bool	re;
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


int	key_hook(int key, t_game *game);

int	terminate(t_game *game);


#endif