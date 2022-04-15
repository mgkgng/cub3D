SRCS =	srcs/cub3D.c srcs/key.c srcs/main.c srcs/parse.c \
		srcs/utils.c srcs/pixel_put.c \
		srcs/draw.c srcs/dda.c srcs/parse_utils.c

NAME = cub3D

OBJS = ${SRCS:.c=.o}

INCLUDES = ./includes/

CFLAG = -Wextra -Wall -Werror

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