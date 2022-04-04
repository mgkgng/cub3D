/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:00:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/04 21:11:59 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	dest = (char *) ft_realloc(dest, dlen + slen + 1);
	/* how to do memcpy from the middle of a string ? */
	i = -1;
	while (dlen + ++i < slen)
		dest[dlen + i] = src[i];
	return (dest);
}
