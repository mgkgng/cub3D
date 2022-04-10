/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:08:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/10 18:25:06 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_surrounded(char **map)
{
	int		i;
	int		j;
	bool	open;

	//** tricky: there can be a line only with space. Should deal with those cases before coming into this function scope.
	//** maybe space value should be TRUE as a bool value.
	//** it's trickier... (because of the space character)
	//** i could just use charmap for this func
	while (map[i])
	{
		j = -1;
		open = false;
		while (map[i][++j])
		{
			if (!open && !(map[i][j] == ' ' || map[i][j] == '1'))
				open = true;
			if (open && map[i][j] == '1')
				open = false;
		}
		if (open == true)
			return (0);
	}
	//** found an error. should be able to check not only horizontally but also vertically.
	return (1);
}