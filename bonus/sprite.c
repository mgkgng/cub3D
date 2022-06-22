/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:47:46 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/22 21:14:00 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	get_sprite_line(t_point p, float theta)
{
	t_line	res;
		
	res.a = tan(theta);
	res.b = -1;
	res.c = p.y - res.a * p.x;
	return (res);
}

float	get_sprite_distance(t_point ray_p, float dist, float theta)
{
	float	new_dist;
	t_point	center;

	center.x = (int) ray_p.x + 0.5;
	center.y = (int) ray_p.y + 0.5;
	t_line	l = get_sprite_line(center, theta + PI / 2);
	new_dist = fabsf(l.a * ray_p.x + l.b + ray_p.y + l.c) / sqrt(pow(l.a, 2) + pow(l.b, 2));
	return (dist + new_dist);
}