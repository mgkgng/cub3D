/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:57:37 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 23:57:38 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*change_spr_img(void *g)
{
	t_game		*game;
	unsigned int	i;

	game = (t_game *) g;
	i = 0;
	while (1)
	{
		game->texture.spr_now = i++ % 4;
		game->hook.re = true;
		usleep(250000);
	}
	return (NULL);
}

void	begin_thread(t_game *game)
{
	pthread_t	th;

	pthread_create(&th, NULL, &change_spr_img, game);
	pthread_detach(th);
	
}