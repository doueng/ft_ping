NAME = ./ft_ping

LIB = ./libft/libft.a

#FLAGS =
FLAGS = -Werror -Wextra -Wall -g

SRC = $(wildcard *.c)

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO)
	@gcc $(SRCO) $(LIB) -o $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
