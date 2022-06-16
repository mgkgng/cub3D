/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:08:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/16 18:38:37 by min-kang         ###   ########.fr       */
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

int	ft_skip(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

int	right_format(char *str)
{
	int	i;

	i = 0;
	i = ft_skip(str);
	if (str[i] != '1')
		end_program("Error 1", 0);
	i = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i--;
	if (str[i] != '1')
		end_program("Error 2", 0);
	return (0);
}

// Check if a 0 is not next to a 1 in all the direction
int	zero_near_space(char **map, int i, int j)
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

void	border_line(char *str)
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
	// for (int j = 0; lines[j]; j++) {
	// 	printf("%s\n", lines[j]);
	// }
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