/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <min-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:49:51 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/27 21:49:51 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	*put_sprite(t_point *spr, int i, int j, int *count)
{

	if (!count)
		spr = ft_calloc(1, sizeof(t_point) + 1);
	else
		spr = ft_realloc(spr, (sizeof(t_point) + 1) * *count);
	spr[*count].x = j;
	spr[*count++].y = i;
	spr[*count].x = -1;
	spr[*count].y = -1;
	return (spr);
}

t_point	*get_sprite(char **map)
{
	int 	i;
	int 	j;
	t_point	*spr;
	int		count;
	
	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'Z')
				spr = put_sprite(spr, i, j, &count);
	}
	if (!count)
		return (NULL);
	return (spr);
}