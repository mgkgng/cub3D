SRCS =	srcs/cub3D.c srcs/key.c srcs/main.c srcs/parse.c \
		srcs/utils.c srcs/draw.c srcs/dda.c srcs/parse_utils.c \
		bonus/minimap.c bonus/mouse.c bonus/sprite.c bonus/door.c\
		srcs/draw_text.c srcs/parse_draw.c srcs/parse_error.c srcs/parse_map.c\
		srcs/key_management.c srcs/movement.c \

NAME = cub3D

OBJS = ${SRCS:.c=.o}

INCLUDES = ./includes/

CFLAG = -Wextra -Wall -Werror -fsanitize=address -g

MLX = -lmlx -framework OpenGL -framework Appkit

MLX_PATH = ./minilibx/

LIB_PATH = ./libft/

all:		${NAME}

${NAME}:	${OBJS}
			make all -C ${LIB_PATH}
			make all -C ${MLX_PATH}
			gcc ${CFLAGS} -I${INCLUDES} -o ${NAME} ${OBJS} ${MLX} ./minilibx/libmlx.a ./libft/libft.a -fsanitize=address
			
.c.o:
			gcc ${CFLAG} -I${INCLUDES} -c $< -o ${<:.c=.o}
			
clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:	all clean fclean re