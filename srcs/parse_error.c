/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:08:30 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/25 21:20:58 by min-kang         ###   ########.fr       */
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
