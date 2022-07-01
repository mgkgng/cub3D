/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:45:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/07/01 18:17:53 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_m.h"

int	check_filename(char *file)
{
	int	len;

	if (open(file, O_RDWR) == -1)
		end_program(file, 1);
	len = ft_strlen(file);
	if (len > 4 && !ft_strcmp(file + len - 4, ".cub"))
		return (1);
	return (0);
}

int	check_texture(char *dir)
{
	if (!ft_strncmp("NO ", dir, 3))
		return (1);
	else if (!ft_strncmp("SO ", dir, 3))
		return (2);
	else if (!ft_strncmp("WE ", dir, 3))
		return (3);
	else if (!ft_strncmp("EA ", dir, 3))
		return (4);
	return (0);
}

void	check_lines(char *line)
{
	static bool	draw_done;
	static bool	map_start;
	static bool	new_line;

	if (!ft_strncmp("C ", line, 2))
		draw_done = true;
	if (draw_done && ft_strchr(" 10NSWE", line[0]))
		map_start = true;
	if (draw_done && map_start && !ft_strcmp("\n", line))
		new_line = true;
	if (new_line && ft_strcmp("\n", line))
		end_program("Error: Wrong format of map", 0);
}
