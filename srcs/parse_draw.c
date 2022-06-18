/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:04:09 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 16:11:31 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_color(char *colstr)
{
	int		col;
	char	**rgb;
	int		i;
	int		j;	

	rgb = ft_split(colstr, ',');
	i = -1;
	while (rgb[++i])
	{
		if (i > 2)
			end_program("Error: rgb", 0);
		j = -1;
		while (rgb[i][++j])
			if (!ft_isdigit(rgb[i][j]))
				end_program("RGB MUST BE NUMERIC", 0);
		if (ft_atoi(rgb[i]) > 255 && ft_atoi(rgb[i]) < 0)
			end_program("RDB MUST BE INFERIOR TO 255", 0);
	}
	col = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | (ft_atoi(rgb[2]));
	free_chartab(rgb);
	return (col);
}

static char	**get_texture(char **file)
{
	int		i;
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
		res[i] = ft_strdup(file[i] + 3);
	}
	res[i] = NULL;
	return (res);
}

t_draw	get_draw(char **lines)
{
	t_draw	draw;

	draw.nswe = get_texture(lines);
	draw.col_floor = get_color(lines[4] + 2);
	draw.col_ceil = get_color(lines[5] + 2);
	return (draw);
}
