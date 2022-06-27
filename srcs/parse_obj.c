/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <min-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:49:51 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/27 22:17:51 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
        printf("ang?\n");
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'Z')
			{
                if (!count)
		            spr = ft_calloc(1, sizeof(t_point) + 1);
	            else
		            spr = ft_realloc(spr, (sizeof(t_point) + 1) * count);
	            spr[count].x = j;
	            spr[count++].y = i;
	            spr[count].x = -1;
	            spr[count].y = -1;
            }
	}
	if (!count)
		return (NULL);
	return (spr);
}