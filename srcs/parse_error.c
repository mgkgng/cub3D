/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:08:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/20 12:18:33 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len > 4 && !ft_strcmp(file + len - 4, ".cub"))
		return (1);
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

// Check if a 0 is not next to a 1 in all the direction
static int	zero_near_space(char **map, int i, int j)
{
	if (i - 1 < 0)
		end_program("Wall", 0);
	else if (i >= ft_tablen(map) - 1)
		end_program("Error 3", 0);
	if (map[i][j + 1] && map[i][j + 1] == ' ')
		end_program("Near a 0 is not a 1", 0);
	if (map[i][j - 1] && map[i][j - 1] == ' ')
		end_program("Near a 0 is not a 1", 0);
	if (map[i + 1][j] && map[i + 1][j] == ' ')
		end_program("Near a 0 is not a 1", 0);
	if (map[i - 1][j] && map[i - 1][j] == ' ')
		end_program("Near a 0 is not a 1", 0);
	return (0);
}

static void	border_line(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i--;
	if (str[i] != '1')
		end_program("Border of map is not a wall", 0);
}

int	is_surrounded(char **lines)
{
	int		i;
	int		j;
	bool	open;

	i = -1;
	while (lines[++i])
	{
		j = -1;
		open = false;
		while (lines[i][++j])
		{
			if (!open && !(lines[i][j] == ' ' || lines[i][j] == '1'))
				open = true;
			if (lines[i][j] == '0')
				zero_near_space(lines, i, j);
			if (open && lines[i][j] == '1')
				open = false;
			border_line(lines[i]);
		}
		if (open == true)
			return (0);
	}
	return (1);
}
