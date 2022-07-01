SRCS =	mandatory/main.c mandatory/cub3d.c \
		mandatory/key.c mandatory/move.c \
		mandatory/parse.c mandatory/parse_draw.c mandatory/parse_map.c \
		mandatory/parse_utils.c mandatory/parse_check1.c mandatory/parse_check2.c \
		mandatory/dda.c mandatory/dda_utils.c \
		mandatory/draw.c mandatory/draw_utils.c \
		mandatory/utils.c

BONUS =	bonus/main.c bonus/cub3d.c \
		bonus/key.c bonus/move.c \
		bonus/parse.c bonus/parse_draw.c bonus/parse_map.c bonus/parse_utils.c \
		bonus/parse_check1.c bonus/parse_check2.c bonus/parse_obj.c \
		bonus/dda.c bonus/dda_utils.c \
		bonus/draw.c bonus/draw_utils.c bonus/draw_sprite.c \
		bonus/utils.c \
		bonus/door.c bonus/list_utils.c bonus/list_utils2.c \
		bonus/minimap.c bonus/minimap_floor.c \
		bonus/mouse.c bonus/thread.c bonus/init.c \

SRC_DIR = srcs

SRC_PATH = $(addprefix $(SRC_DIR)/, $(SRCS))
BONUS_PATH = $(addprefix $(SRC_DIR)/, $(BONUS))

NAME = cub3D

ifndef WITH_BONUS
	OBJS = ${SRC_PATH:.c=.o}
else
	OBJS = ${BONUS_PATH:.c=.o}
endif

INCLUDES = ./includes/

CFLAG = -Wextra -Wall -Werror

MLX = -lmlx -framework OpenGL -framework Appkit

MLX_PATH = ./minilibx/

LIB_PATH = ./libft/

GREEN	:= "\033[0m\033[1;32m"
CYAN	:= "\033[0m\033[1;36m"
RESET	:= "\033[0m"

.c.o:
		@printf ${GREEN}"\r\033[KCompiling objects... "${RESET}"⏳"
		@gcc ${CFLAG} -I${INCLUDES} -c $< -o $(<:.c=.o) 

all:	${NAME}

bonus:
		@make WITH_BONUS=1 all

${NAME}:	${OBJS}
			@printf "\n"
			@printf ${GREEN}"\r\033[KCompiling libft...⏳\n"${RESET}
			@make all -C ${LIB_PATH}
			@printf ${GREEN}"\r\033[KCompiling minilibX...⏳\n"${RESET}
			@make all -C ${MLX_PATH}
			@gcc ${CFLAG} -I${INCLUDES} -o ${NAME} ${OBJS} ${MLX} minilibx/libmlx.a ./libft/libft.a

clean:
			@rm -f ${SRC_PATH:.c=.o} ${BONUS_PATH:.c=.o} 
			@make clean -C ${LIB_PATH}

fclean:		clean
			@rm -f ${NAME}
			@make fclean -C ${LIB_PATH}

re:			fclean all

.PHONY:	all clean fclean re