/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/25 17:03:01 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_game	parse(char *filename)
{
	char	**lines;
	t_game	game;

	if (!check_filename(filename))
		end_program("Error: Wrong file format", 0);
	lines = get_lines(get_fd(filename));
	game.draw = get_draw(lines);
	game.map = get_map(lines);
	free_chartab(lines);
	return (game);
}
