/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:03:47 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/16 17:17:54 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		end_program(filename, 1);
	}
	return (fd);
}

/*int	terminate_parse(char *mapstr, char **map, char *set)
{
	free(mapstr);
	free(map);
	if (set)
		free(set);
	return (0);
}*/

int	ft_tablen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
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

int	verif_texture(char *dir)
{
	if (!ft_strncmp("NO", dir, 2))
		return (1);
	else if (!ft_strncmp("SO", dir, 2))
		return (2);
	else if (!ft_strncmp("WE", dir, 2))
		return (3);
	else if (!ft_strncmp("EA", dir, 2))
		return (4);
	return (0);
}

int	get_color(char *colstr)
{
	int		col;
	char	**rgb;

	rgb = ft_split(colstr, ',');
	// il manque gestion d'erreur
	col = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | (ft_atoi(rgb[2]));
	free(rgb);
	return (col);
}