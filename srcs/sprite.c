/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:06:56 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/25 15:14:37 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_list	*sort_linked_list(t_list *spr, t_game *game)
{
	t_list	*sort;
	t_list	*tmp;
	t_list	*tt;
	float	dist;

	tt = spr;
	while (tt)
	{
		tmp = tt;
		dist = (game->map.pos.x - tt->pos.x) * (tt->pos.x - tt->pos.x) + (tt->pos.y - tt->pos.y) * (tt->pos.y - tt->pos.y);


	}
}

