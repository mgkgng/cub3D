/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:59:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/16 00:05:09 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//** this code should be studied and modified (or optimized.)
//** for now, i'm using it in order to advance as soon as possible.

//tomorrow after testing it, i'll simplify it by creating another sub-structure inside of GUI structure
void	minimap_pixel_put(t_gui *gui, int x, int y, int color)
{
	char	*dst;

	dst = gui->mini_addr + (y * gui->mini_len + x * (gui->mini_pixel / 8));
	*(unsigned int *) dst = color;
}

void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color)
{
	char	*dst;

	dst = gui->addr + (y * gui->line_len + x * (gui->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}