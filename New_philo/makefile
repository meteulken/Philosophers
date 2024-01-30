NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

SRC = philo.c philo_utils.c ./mallocCollector/mallocCollector.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(OBJ)

re: fclean all