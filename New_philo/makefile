NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
SRC = philo.c philo_die.c philo_utils.c philo_utils2.c philo_init.c philo_init2.c ./mallocCollector/mallocCollector.c

OBJDIR := objs
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
