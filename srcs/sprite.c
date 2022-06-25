/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:06:56 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/25 21:31:26 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*sort_linked_list(t_list *spr, t_game *game)
{
	t_list	*sort;
	t_list	*tmp;
	t_list	*tt;
	float	dist;
	float	test;
	
	tt = spr;
	while (tt)
	{
		tmp = tt;
		dist = (game->map.pos.x - tt->pos.x) * (tt->pos.x - tt->pos.x) + (tt->pos.y - tt->pos.y) * (tt->pos.y - tt->pos.y);
		if ()
	}
}

