/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/16 23:04:30 by min-kang         ###   ########.fr       */
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
	return (game);
}