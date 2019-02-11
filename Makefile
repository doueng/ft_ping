NAME = ./ft_ping

LIB = ./libft/libft.a

FLAGS =
#FLAGS = -Werror -Wextra -Wall -g

SRC = $(wildcard *.c)

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO)
	make -C libft
	@gcc $(SRCO) $(LIB) -o $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO)
	@/bin/rm -f compile_commands.json
	@/bin/rm -f ft_ping.dSYM

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
