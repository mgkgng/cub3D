/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:13:58 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 04:38:11 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	end_program(char *str, int tag)
{
	if (tag == 1)
		ft_putstr_fd("Error: cannot read file ", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color)
{
	char	*dst;

	dst = gui->addr + (y * gui->line_len + x * (gui->bits_per_pixel / 8));
	//if (y < 600)
	*(unsigned int *) dst = color;
}

int	terminate(t_game *game)
{
	free(game->map.map_wall);
	free(game->map.map_move);
	free(game->draw.nswe);
	exit(0);
}

t_door	*ft_lstnew(t_point pos, float dist)
{
	t_door	*res;

	res = ft_calloc(1, sizeof(t_door));
	res->pos = pos;
	res->dist = dist;
	return (res);
}

void	ft_lstadd_front(t_door **alst, t_door *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstadd_back(t_door **alst, t_door *new)
{
	t_door	*begin;

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

void	free_lst(t_door *lst)
{
	t_door	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	free_chartab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}