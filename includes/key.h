/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:39:16 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 19:02:35 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

typedef enum e_key {
	KEY_ESC = 53,
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	KEY_TURN_L = 123,
	KEY_TURN_R = 124,
	KEY_MINI = 46,
	KEY_MINI_ZOOM_IN = 126,
	KEY_MINI_ZOOM_OUT = 125,
} t_key;

typedef enum e_pressed {
	ESC = 1 << 0,
	UP = 1 << 1,
	DOWN = 1 << 2,
	LEFT = 1 << 3,
	RIGHT = 1 << 4,
	TURN_L = 1 << 5,
	TURN_R = 1 << 6,
	DOOR = 1 << 7,
} t_pressed;

#endif