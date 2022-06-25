/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:49:53 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/22 21:12:40 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_lstnew(t_point pos, float dist, int type, t_point map_pos)
{
	t_list	*res;

	res = ft_calloc(1, sizeof(t_list));
	res->pos = pos;
	res->dist = dist;
	res->type = type;
	res->map_pos.x = map_pos.x;
	res->map_pos.y = map_pos.y;
	return (res);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;

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

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
