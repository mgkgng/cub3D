/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/06 10:54:07 by min-kang         ###   ########.fr       */
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
#include "parse.h"

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

typedef struct s_line {
	t_point	a;
	t_point	b;
}	t_line;

typedef struct s_draw {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		col_floor;
	int		col_ceil;
}	t_draw;

typedef struct s_map {
	int		width;
	int		height;
	char	**map;
	t_line	*lines;
	t_point	pos;
	t_point	dir;
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
}	t_game;

typedef struct s_raycast {
	double	x1;
	double	x2;
	double	x3;
	double	x4;
	double	y1;
	double	y2;
	double	y3;
	double	y4;
}	t_raycast;

/* parse */
t_game	parse(char *file);

/* error */
void	error(int c);

#endif