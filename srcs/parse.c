/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:01:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/04 20:20:34 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_fileformat(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (!ft_strcmp(file, ".cub"))
		return (1);
	// there would be some more tricky cases
	return (0);
}

t_game	parse(char *file)
{
	if (!check_fileformat)
		error(2);
	// ... now how to parse? how kind of categories of information?
}