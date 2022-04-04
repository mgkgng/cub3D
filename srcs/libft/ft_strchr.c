/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:25:56 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/03 22:22:15 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!c)
		return ((char *) s + ft_strlen(s));
	i = -1;
	while (s[++i])
		if (s[i] == (char) c)
			return ((char *) s + i);
	return (0);
}
