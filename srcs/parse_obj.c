/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <min-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:49:51 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 16:49:59 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_sprite(t_map *map, int i, int j, int count)
{
	if (!count)
		map->spr = ft_calloc(2, sizeof(t_point));
	else
		map->spr = ft_realloc(map->spr, sizeof(t_point) * (count + 2));
		map->spr[count].x = j;
		map->spr[count].y = i;
		map->spr[count].x = -1;
		map->spr[count].y = -1;
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
				put_sprite(map, i, j, count++);
	}
	map->spr_nb = count;
	if (!count)
		map->spr = NULL;
}
