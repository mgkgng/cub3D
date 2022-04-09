/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:59:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/09 13:02:20 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//** this code should be studied and modified (or optimized.)
//** for now, i'm using it in order to advance as soon as possible.

void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color)
{
	char	*dst;

	dst = gui->addr + (y * gui->line_len + x * (gui->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}