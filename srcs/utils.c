/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:13:58 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 23:55:21 by min-kang         ###   ########.fr       */
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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!color)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	terminate(t_game *game)
{
	free(game->map.map_wall);
	free(game->map.map_move);
	free(game->draw.nswe);
	exit(0);
}

float	get_angle(float old, float change)
{
	float	res;
	res = old + change;
	if (res > M_PI * 2)
		return (res - M_PI * 2);
	else if (res < 0)
		return (res + M_PI * 2);
	return (res);
}

void	free_chartab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}