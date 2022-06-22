/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:47:46 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/22 21:01:42 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	get_sprite_line(t_point p, float theta)
{
	t_line	res;
	float	a;
	float	b;
		
	res.a = tan(theta);
	res.b = -1;
	res.c = p.y - a * p.x;
	return (res);
}

float	get_sprite_distance(t_line l, t_point ray_p, float dist)
{
	float	new_dist;

	new_dist = abs(l.a * ray_p.x + l.b + ray_p.y + l.c) / sqrt(pow(l.a, 2) + pow(l.b, 2));
	return (dist + new_dist);
}