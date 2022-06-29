/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:00:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 18:09:09 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# define BLOCKSIZE 18
# define MINI_X 20
# define MINI_Y 20
# define MINI_SQUARE 50
# define MINI_W 250
# define MINI_H 250
# define SCREEN_X 920
# define SCREEN_Y 600

typedef struct s_dda {
	float	delta;
	int		incre;
	int		side;
}	t_dda;

#endif