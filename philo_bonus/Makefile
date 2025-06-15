SRCS =  main.c parsing.c utils.c  clean.c utils3.c utils4.c init.c utils2.c \
	philo_routine.c monitor.c time_utils.c simulation.c philo_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo_bonus

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
.SECONDARY:$(OBJS)