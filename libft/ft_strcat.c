/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:00:43 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 00:49:10 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	size_t	dlen;
	size_t	slen;

	if (!dest)
		return (ft_strdup(src));
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	dest = (char *) ft_realloc(dest, dlen + slen + 1);
	ft_strcpy(dest + dlen, src);
	return (dest);
}
