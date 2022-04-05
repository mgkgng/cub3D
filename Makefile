SRCS =	srcs/cub3D.c srcs/key.c srcs/main.c srcs/mouse.c srcs/parse.c \
		srcs/raycasting.c srcs/utils.c

NAME = cub3D

OBJS = ${SRCS:.c=.o}

INCLUDES = ./includes/

CFLAG = -Wextra -Wall -Werror

MLX = -lmlx -framework OpenGL -framework Appkit

MLX_PATH = ./minilibx/

LIB_PATH = ./libft/

all:		${NAME}

${NAME}:	${OBJS}
			gcc ${CFLAGS} -I${INCLUDES} -o ${NAME} ${OBJS} ${MLX} libft/libft.a
			
.c.o:
			gcc ${CFLAG} -I${INCLUDES} -c $< -o ${<:.c=.o}
			
clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:	all clean fclean re