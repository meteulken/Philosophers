CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

NAME = philo_bonus
SRCS = init.c parse.c routine.c utils.c main.c time.c

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

all: ${NAME}

clean:

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re