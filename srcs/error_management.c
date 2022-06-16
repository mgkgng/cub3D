/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:35:08 by mlecherb          #+#    #+#             */
/*   Updated: 2022/06/16 15:02:14 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**file_to_tab(int fd)
{
	int		ret;
	char	buf[2];
	char	*line;

	ret = 0;
	ret = read(fd, buf, 1);
	buf[ret] = '\0';
	line = ft_strdup(buf);
	while (ret > 0)
	{
		ret = read(fd, buf, 1);
		buf[ret] = '\0';
		line = ft_strjoin(line, buf);
	}
	return (ft_split(line, '\n'));
}

char	**grep_texture(char **file, t_info info)
{
	char	**texture;
	int i;
	int fd_test;

	i = 0;
	texture = malloc(sizeof(char *) * 5);
	while (i++ < 3)
		if (verif_texture(file[i]) == 0)
			error_quit("Error in texture");
	i = 0;
	while (i < 4) {
		if (i != verif_texture(file[i]) - 1)
			error_quit("mauvais");
		texture[i] = ft_strdup(file[i]);
		fd_test = open(texture[i] + 3, O_RDONLY);
		if (fd_test == -1)
			error_quit("Bad textures's file name");
		close(fd_test);
		i++;
	}
	texture[i] = NULL;
	info.i = i;
	return (texture);
}

int	**grep_rgb(char **file, t_info info)
{
	char	**rgb;
	int j;

	j = 0;
	rgb = malloc(sizeof(char *) * 3);
	if (file[info.i][0] != 'F' || file[info.i + 1][0] != 'C')
		error_quit("Bad rgb");
	while (j < 2) 
	{
		rgb[j] = ft_strdup(file[info.i]);
		info.i++;
		j++;
	}
	rgb[j] = NULL;
	int	**f = malloc(sizeof(int) * 3);
	// int	*c = malloc(sizeof(int) * 3);
	char	**line_f = ft_split(rgb[0] + 2, ',');
	char	**line_c = ft_split(rgb[1] + 2, ',');
	j = 0;
	while (j < 3) {
		f[0][j] = ft_atoi(line_f[j]);
		f[1][j] = ft_atoi(line_c[j]);
		j++;
	}
	return (f);
}

char	**get_char_map(char **file, t_info info)
{
	char	**map; 
	int j;
	
	map = malloc(sizeof(char *) * (tab_len(file) - info.i + 1));
	j = 0;
	while (file[info.i])
	{
		map[j] = ft_strdup(file[info.i]);
		j++;
		info.i++;
	}
	map[j] = NULL;
	return (map);
}