/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:36:27 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/27 20:25:16 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_spr	*ft_lstnew_spr(int x, int y)
{
	t_list	*res;

	res = ft_calloc(1, sizeof(t_list));
	res->pos.x = x;
	res->pos.y = y;
	res->next = NULL;
	return (res);
}


void	ft_lstadd_back_spr(t_spr **alst, t_spr *new)
{
	t_spr	*begin;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	begin = *alst;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}

t_spr	*get_sprite(char **map)
{
	int 	i;
	int 	j;
	t_spr	*sprite;
	
	sprite = NULL;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'Z')
				ft_lstadd_back_spr(&sprite, ft_lstnew_spr(j, i));
			j++;
		}
		i++;
	}
	return (sprite);
}