#include "cub3D.h"

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

	while (map[i])
		i++;
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
	info.file = file_to_tab(fd);
	info.text = grep_texture(info.file, info);
	info.rgb = grep_rgb(info.file, info);
	info.map = get_char_map(info.file, info);
	return (info);
}
