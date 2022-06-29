/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <min-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:49:05 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 15:38:05 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

typedef struct s_sprite {
    float   x;
    float   y;
    float   inverse;
    float   x_trans;
    float   y_trans;
    float   x_screen;
    float   w;
    float   h;
    int     start_x;
    int     start_y;
    int     end_x;
    int     end_y;
}   t_sprite;

#endif