SRCS =	ft_bzero.c ft_calloc.c ft_memcpy.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
		ft_strcat.c ft_strlen.c ft_strcmp.c \
		ft_realloc.c get_next_line.c ft_isdigit.c \
		ft_atoi.c ft_strncmp.c ft_strtrim.c \
		ft_substr.c ft_strjoin.c ft_strcpy.c \

NAME = libft.a

OBJS = ${SRCS:.c=.o}

INCLUDES = ../includes/

CFLAG = -Wextra -Wall -Werror #-g -fsanitize=address

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
		
.c.o:
			gcc ${CFLAG} -I${INCLUDES} -c $< -o ${<:.c=.o}
			
clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:	all clean fclean re