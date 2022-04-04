/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:22:26 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/04 20:22:27 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error(int c)
{
	if (c == 1)
		ft_putendl_fd("Invalid argument input.", 2);
	if (c == 2)
		ft_putendl_fd("Wrong file format.", 2);
	exit(1);
}