SRCS =	srcs/main.c srcs/cub3d.c \
		srcs/key.c srcs/move.c \
		srcs/parse.c srcs/parse_draw.c srcs/parse_map.c srcs/parse_utils.c \
		srcs/parse_check1.c srcs/parse_check2.c srcs/parse_obj.c \
		srcs/dda.c srcs/dda_utils.c \
		srcs/draw.c srcs/draw_utils.c srcs/draw_sprite.c\
		srcs/utils.c \
		bonus/door.c bonus/list_utils.c bonus/list_utils2.c \
		bonus/minimap.c bonus/mouse.c bonus/thread.c bonus/init.c \
	
NAME = cub3D

OBJS = ${SRCS:.c=.o}

INCLUDES = ./includes/

CFLAG = -Wextra -Wall -Werror #-g -fsanitize=address

MLX = -lmlx -framework OpenGL -framework Appkit

MLX_PATH = ./minilibx/

LIB_PATH = ./libft/

all:		${NAME}

${NAME}:	${OBJS}
			make all -C ${LIB_PATH}
			make all -C ${MLX_PATH}
			gcc ${CFLAGS} -I${INCLUDES} -o ${NAME} ${OBJS} ${MLX} minilibx/libmlx.a ./libft/libft.a
			
.c.o:
			gcc ${CFLAG} -I${INCLUDES} -c $< -o ${<:.c=.o}
			
clean:
			rm -f ${OBJS}
			make clean -C ${LIB_PATH}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:	all clean fclean re