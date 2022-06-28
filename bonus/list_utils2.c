/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:21:29 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/28 11:57:06 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manip_list(t_list **one, t_list *other)
{
	t_list	*tmp;

	if ((*one)->dist < other->dist)
	{
		ft_lstadd_front(one, ft_lstnew(other->pos, other->dist, other->type, other->map_pos));
		return ;
	}
	tmp = (*one)->next;
	ft_lstadd_back(one, ft_lstnew(other->pos, other->dist, other->type, other->map_pos));
	(*one)->next->next = tmp;
}

t_list	*copy_list(t_list *lst)
{	
	t_list	*res;

	res = NULL;
	while (lst)
	{
		ft_lstadd_back(&res, ft_lstnew(lst->pos, lst->dist, lst->type, lst->map_pos));
		lst = lst->next;
	}
	return (res);
}

void	combine_list(float dist, t_list **origin, t_list *compare)
{
	//t_list	*begin;
	t_list	*now_compare;

	//begin = *origin;
	now_compare = compare;
	if (!*origin)
	{
		while (now_compare)
		{
			if (now_compare->dist < dist)
			{				
				*origin = copy_list(now_compare);
				return ;
			}
			now_compare = now_compare->next;
		}
	}
	while (now_compare) // i should take care here
	{
		if (now_compare->dist < dist)
		{
			while ((*origin)->next && (*origin)->next->dist > now_compare->dist)
				*origin = (*origin)->next;
			manip_list(origin, now_compare);
		}
		now_compare = now_compare->next;
	}
}
