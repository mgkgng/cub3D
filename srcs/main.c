/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:46:02 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/13 17:51:39 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		error(1);
	return (cub3D(parse(argv[1])));
}

void	aff_tab(char **map)
{
	int	i = 0;

	if (!map)
		return ;
	while (map[i])
		printf("%s\n", map[i++]);
}

int	tab_len(char **map) {
	int	i = 0;

	while (map[i]) {
		i++;
	}
	return (i);
}

void	error_quit(char * msg) {
	printf("%s\n", msg);
	exit (1);
}

int	verif_texture(char *dir)
{
	if (dir[0] == 'N' && dir[1] == 'O')
		return (1);
	else if (dir[0] == 'S' && dir[1] == 'O')
		return (2);
	else if (dir[0] == 'W' && dir[1] == 'E')
		return (3);
	else if (dir[0] == 'E' && dir[1] == 'A')
		return (4);
	return (0);
}

t_info parser(char *file)
{
	int		fd;
	// int		ret;
	// char	buf[2];
	// char	*line;
	t_info	info;

	printf("%s\n", file);
	fd = open(file, O_RDONLY);
	info.i = 0;
	// ret = 0;
	// ret = read(fd, buf, 1);
	// buf[ret] = '\0';
	// line = ft_strdup(buf);
	// while (ret > 0)
	// {
	// 	ret = read(fd, buf, 1);
	// 	buf[ret] = '\0';
	// 	line = ft_strjoin(line, buf);
	// }
	// char	**file = ft_split(line, '\n');
	info.file = file_to_tab(fd);
	// file_to_tab(int fd);
	// if (tab_len(info.file) < 9)
	// 	error_quit("Bad line numbers");
	// char	**texture = malloc(sizeof(char *) * 5);
	// int i = 0;
	// // aff_tab(file);
	// while (i++ < 3)
	// 	if (verif_texture(file[i]) == 0)
	// 		error_quit("Error in texture");
	// i = 0;
	// // printf("%s\n", file[0]);
	// int fd_test;
	// while (i < 4) {
	// 	if (i != verif_texture(file[i]) - 1)
	// 		error_quit("mauvais");
	// 	texture[i] = ft_strdup(file[i]);
	// 	fd_test = open(texture[i] + 3, O_RDONLY);
	// 	if (fd_test == -1)
	// 		error_quit("Bad textures's file name");
	// 	close(fd_test);
	// 	i++;
	// }
	// texture[i] = NULL;
	info.text = grep_texture(info.file, info);
	// printf("---------------\nTEXTURE: \n");
	// aff_tab(info.text);
	// printf("---------------\nRGB TAB : \n");
	// Attribuer dans 4 char * les path des texture
	// char	**rgb = malloc(sizeof(char *) * 3);
	// int j = 0;
	// if (file[i][0] != 'F')
	// 	error_quit("Bad rgb");
	// if (file[i + 1][0] != 'C')
	// 	error_quit("Bad rgb");
	// while (j < 2) {
	// 	rgb[j] = ft_strdup(file[i]);
	// 	i++;
	// 	j++;
	// }
	// rgb[j] = NULL;
	// aff_tab(rgb);
	// printf("---------------\nRGB : \n");
	// int	*f = malloc(sizeof(int) * 3);
	// int	*c = malloc(sizeof(int) * 3);
	// char	**line_f = ft_split(rgb[0] + 2, ',');
	// char	**line_c = ft_split(rgb[1] + 2, ',');
	// j = 0;
	// while (j < 3) {
	// 	f[j] = ft_atoi(line_f[j]);
	// 	c[j] = ft_atoi(line_c[j]);
	// 	j++;
	// }
	// // grep_rgb(char **file, int i);
	info.rgb = grep_rgb(info.file, info);
	// j = 0;
	// while (j < 3)
	// {
	// 	printf("[%d]", f[j]);
	// 	j++;
	// }
	// printf("\n");
	// j = 0;
	// while (j < 3)
	// {
	// 	printf("[%d]", c[j]);
	// 	j++;
	// }
	// printf("\n");
	// printf("---------------\nMAP : \n");
	// char	**map = malloc(sizeof(char *) * (tab_len(file) - i + 1));
	// j = 0;
	// while (file[i])
	// {
	// 	map[j] = ft_strdup(file[i]);
	// 	j++;
	// 	i++;
	// }
	// map[j] = NULL;
	info.map = get_char_map(info.file, info);
	// aff_tab(map);
	// printf("---------------\n");
	return (info);
}
