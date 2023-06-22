CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

NAME = philo
SRCS = init.c parse.c routine.c utils.c die.c main.c time.c

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

all: ${NAME}

clean:

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re