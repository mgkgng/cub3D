/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:35:42 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/07 19:00:02 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "cub3D.h"

# define ANGLE 90

typedef struct s_raycast {
	// f(x) = ax + b func which represents direction vector
	float	slope;
	float	intercept;
	t_point	pos_vec;
}	t_raycast;

#endif