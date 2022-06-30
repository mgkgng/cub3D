/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:46:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:55:10 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_m.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		end_program("Error: Invalid number of arguments", 0);
	return (cub3d(parse(argv[1])));
}
