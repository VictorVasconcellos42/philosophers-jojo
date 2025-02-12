NAME=philo

SRC= main.c parser.c dinner.c utils.c monitor.c
OBJ= $(SRC:.c=.o)

FLAGS= -ggdb3 -Wall -Wextra -Werror -pthread
CC=cc

all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
#	rm -f *.log

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all exec clean fclean re
