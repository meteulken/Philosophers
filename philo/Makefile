NAME = philo
CC = cc -Wall -Wextra -Werror
SOURCE = philo_utils.c philo.c philo_arg_control.c philo_create.c philo_routine.c philo_free.c philo_time.c philo_die.c

OBJ = $(SOURCE:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
all: $(NAME)


c: clean
clean:
	@rm -rf *.o

f: fclean
fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all f c