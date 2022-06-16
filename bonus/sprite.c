/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:27:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 00:37:29 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_sprite	*ft_lstnew(char *name, t_game *game)
{
	t_sprite	*new;

	new = malloc(sizeof(t_sprite));
	if (new == NULL)
		return (NULL);
	new->h = 64;
	new->w = 64;
	new->img = mlx_xpm_file_to_image(game->mlx, name, &new->w, &new->h);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, &new->line_length, &new->endian);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_sprite **alst, t_sprite *new)
{
	t_sprite	*temp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	else
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	init_sprite(t_game *game)
{
	game->spr = ft_lstnew("./sprite/Couche-1.xpm", game);
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-2.xpm", game));
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-3.xpm", game));
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-4.xpm", game));
	ft_lstadd_back(&game->spr, ft_lstnew("./sprite/Couche-5.xpm", game));
}
