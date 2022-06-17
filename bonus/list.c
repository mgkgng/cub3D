/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:49:53 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 23:14:51 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_list	*ft_lstnew(t_point pos, float dist)
{
	t_list	*res;

	res = ft_calloc(1, sizeof(t_list));
	res->pos = pos;
	res->dist = dist;
	//printf("....test....%p\n", &res->next);
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

void	free_lst(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	manip_list(t_list **one, t_list *other)
{
	t_list	*tmp;
	
	if ((*one)->dist < other->dist)
	{
		ft_lstadd_front(one, ft_lstnew(other->pos, other->dist));
		return ;
	}
	tmp = (*one)->next;
	ft_lstadd_back(one, ft_lstnew(other->pos, other->dist));
	(*one)->next->next = tmp;
}

t_list	*copy_list(t_list *lst)
{	
	t_list	*res;

	res = NULL;
	while (lst)
	{
		ft_lstadd_back(&res, ft_lstnew(lst->pos, lst->dist));
		lst = lst->next;
	}
	return (res);
}

void	combine_list(float dist, t_list **origin, t_list *compare)
{
	t_list	*begin;
	t_list	*now_compare;

	begin = *origin;
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
	while (now_compare)
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