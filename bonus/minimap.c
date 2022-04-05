/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:18:52 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/05 17:59:27 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_line_per_x(t_point a, t_point b, double slope)
{
	double	intercept;
	double	delta;

	intercept = a.y - a.x * slope;
	delta = (a.x > b.x) ? -1 : 1;
	while (a.x + delta != b.x)
		draw_func(a.x + delta, roundf(slope * (a.x + delta) + intercept), COLOR); // something like that
	
}

static void	draw_line_per_y(t_point a, t_point b, double slope)
{
	double intercept;
	int		delta;

	intercept = a.y - a.x * slope;
	delta = (a.y > b.y) ? -1 : 1;
	while (a.y + delta != b.y)
		draw_func(roundf(a.x * slope - intercept), a.y + delta++); // something like that
}

void	draw_line(t_point a, t_point b)
{
	double	delta_x;
	int		delta;
	int		endpoint;
	double	slope;

	delta_x = b.x - a.x;
	if (!delta_x)
	{
		delta = (a.y > b.y) ? -1 : 1;
		while (a.y + delta != b.y)
			draw_func(a.x, a.y + delta++);
		return ;
	}
	slope = (b.y - a.y) / delta_x;
	if (slope < 1 && slope > -1)
		draw_line_per_x(a, b, slope);
	else
		draw_line_per_y(a, b, slope);
}

void	
void	draw_minimap(t_map map)
{
	
}