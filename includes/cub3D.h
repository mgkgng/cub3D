/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/05 01:41:10 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <mlx.h>
#include "libft.h"
#include "hook.h"

typedef struct s_game {
	
}	t_game;

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
	t_hook	hook;
} 	t_gui;

typedef struct s_hook {
	bool	re;
}	t_hook;

/* parse */
t_game	parse(char *file);

/* error */
void	error(int c);

#endif