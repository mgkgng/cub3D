/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:03:47 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/17 15:59:30 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	terminate_parse(char *mapstr, char **map, char *set)
{
	free(mapstr);
	free(map);
	if (set)
		free(set);
	return (0);
}

int	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 4 && !ft_strcmp(file + len - 4, ".cub"))
		return (1);
	// there would be some more tricky cases
	return (0);
}

int	check_fileformat(char *mapstr, char **map)
{
	int	i;
	int	j;
	char	*set;

	// check n.1 : is there any other character than one of the ones needed to be
	set = ft_strdup(" 210NSWE");
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j]) {
			//printf("%d---%d---\n", i ,j);
			if (!ft_strchr(set, map[i][j]))
				return (terminate_parse(mapstr, map, set));
		}
	}
	// check n.2 : is the map is well surrounded by wall?
	// check n.3 : is there only one character?
	return (1);
}

int	get_color(char *colstr)
{
	int		col;
	char	**rgb;

	rgb = ft_split(colstr, ',');
	col = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | (ft_atoi(rgb[2]));
	free(rgb);
	free(colstr);
	return (col);
}