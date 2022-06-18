/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:02:19 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 14:38:31 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_hook(int x, int y, t_hook *hook)
{
	if (x < 0 || y < 0 || x > SCREEN_X || y > SCREEN_Y)
		return (1);
	if (x < hook->x_prev)
		hook->m_dir = -1;
	else
		hook->m_dir = 1;
	hook->m_turn = abs(hook->x_prev - x);
	hook->x_prev = x;
	hook->m_re = true;
	return (0);
}
