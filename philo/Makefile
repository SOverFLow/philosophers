CC=cc
NAME=philo
SRC=philo.c ft_atoi.c errors.c utils.c
CFLAGS=-Wall -Wextra -Werror -pthread
OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean:clean 
	rm -f $(NAME)

re:fclean $(NAME)
