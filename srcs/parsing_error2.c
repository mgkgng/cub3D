/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:41:49 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/22 21:13:30 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	door_check(char	**map, int i, int j)
{
	int	count_right;
	int	count_left;

	count_left = 0;
	count_right = 0;
	if (map[i][j + 1] == '1')
		count_right++;
	if (map[i][j - 1] == '1')
		count_right++;
	if (map[i + 1][j] == '1')
		count_left++;
	if (map[i - 1][j] == '1')
		count_left++;
	if (count_left == 2 || count_right == 2)
		return ;
	else
		end_program("Door must be surrounded on their side by a wall", 0);
}

void	door_error(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				door_check(map, i, j);
			j++;
		}
		i++;
	}
}
