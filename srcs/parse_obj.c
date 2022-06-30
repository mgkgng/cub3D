/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:49:51 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 18:43:16 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	*put_sprite(t_map *map, int i, int j, int count)
{
	t_point	*res;

	if (!count)
		res = ft_calloc(2, sizeof(t_point));
	else
	{
		res = ft_calloc(count + 2, sizeof(t_point));
		ft_memcpy(res, map->spr, count * sizeof(t_point));
	}
	res[count].x = j + 0.5;
	res[count].y = i + 0.5;
	res[count + 1].x = -1;
	res[count + 1].y = -1;
	return (res);
}

void	get_sprite(t_map *map, char **charmap)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (charmap[++i])
	{
		j = -1;
		while (charmap[i][++j])
			if (charmap[i][j] == 'Z')
				map->spr = put_sprite(map, i, j, count++);
	}
	map->spr_nb = count;
	if (!count)
		map->spr = NULL;
}
