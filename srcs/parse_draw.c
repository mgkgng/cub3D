/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:04:09 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/16 23:11:34 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_color(char *colstr)
{
	int		col;
	char	**rgb;

	rgb = ft_split(colstr, ',');
	// il manque gestion d'erreur
	col = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | (ft_atoi(rgb[2]));
	free(rgb);
	return (col);
}

static char	**get_texture(char **file)
{
	int 	i;
	char	**res;

	res = malloc(sizeof(char *) * 5);
	i = -1;
	while (++i < 4)
		if (i != verif_texture(file[i]) - 1)
			end_program("Wrong format for texture information.", 0);
	i = -1;
	while (++i < 4)
	{
		get_fd(file[i] + 3);
		res[i]= ft_strdup(file[i] + 3);
	}
	res[i] = NULL;
	return (res);
}

t_draw	get_draw(char **lines)
{
	t_draw	draw;
	
	draw.nswe = get_texture(lines);
	draw.col_floor = get_color(lines[4] + 2);
	draw.col_ceil = get_color(lines[5]);
	return (draw);
}