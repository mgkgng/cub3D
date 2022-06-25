/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:47:46 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/22 22:04:20 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	get_sprite_line(t_point p, float theta)
{
	t_line	res;
		
	res.a = tan(theta);
	res.b = -1;
	res.c = p.y + 0.5 - res.a * (p.x + 0.5);
	return (res);
}

float	get_sprite_dist(t_point ray_p, float dist, float theta)
{
	float	new_dist;
	t_line	l;

	l = get_sprite_line(ray_p, theta + PI / 2);
	new_dist = fabs(l.a * ray_p.x + l.b + ray_p.y + l.c) / sqrtf(powf(l.a, 2) + powf(l.b, 2));
	return (dist + new_dist);
}