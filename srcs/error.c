/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:08:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/10 16:40:45 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	end_program(char *str)
{
	printf("%s\n", str);
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
		end_program("Error");
	i = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i--;
	if (str[i] != '1')
		end_program("Error");
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// Check if a 0 is not next to a 1 in all the direction
int	zero_near_space(char **map, int i, int j)
{
	if (i - 1 < 0)
		end_program("Error");
	else if (i + 1 > ft_tablen(map) - 1)
		end_program("Error");
	if (map[i][j + 1] && map[i][j + 1] == ' ')
		end_program("Error");
	if (map[i][j - 1] && map[i][j - 1] == ' ')
		end_program("Error");
	if (map[i + 1][j] && map[i + 1][j] == ' ')
		end_program("Error");
	if (map[i - 1][j] && map[i - 1][j] == ' ')
		end_program("Error");
	return (0);
}

int	is_surrounded(char **map)
{
	int		i;
	int		j;
	bool	open;

	//** tricky: there can be a line only with space. Should deal with those cases before coming into this function scope.
	//** maybe space value should be TRUE as a bool value.
	//** it's trickier... (because of the space character)
	//** i could just use charmap for this func
	i = 0;
	while (map[i])
	{
		j = -1;
		open = false;
		// Check if the first and the last char of the ligne is a 1
		// right_format(map[i]);																																																end_program("Error");
		while (map[i][++j])
		{
			if (!open && !(map[i][j] == ' ' || map[i][j] == '1'))
				open = true;
			if (map[i][j] == '0')
				zero_near_space(map, i, j);
			if (open && map[i][j] == '1')
				open = false;
		}
		i++;
		if (open == true)
			return (0);
	}
	//** found an error. should be able to check not only horizontally but also vertically.
	return (1);
}