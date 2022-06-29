/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:02:34 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 18:17:00 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

typedef struct s_list {
	t_point			pos;
	t_point			map_pos;
	float			dist;
	struct s_list	*next;
}	t_list;

#endif