CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
PHILO = philo
SRCS = control.c \
		die.c \
		init.c \
		main.c \
		routine.c \
		time.c \
		utils.c \
		mutexes.c \
		threads.c

OBJS = $(SRCS:.c=.o)

all:  $(PHILO)

$(PHILO) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(PHILO)
	@echo "FINISH"

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(PHILO)
	rm -rf $(OBJS)

fclean: clean

re: fclean all

.PHONY: clean re fclean all
