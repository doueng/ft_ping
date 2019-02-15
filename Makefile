NAME = ./ft_ping
HEADER = ./ft_ping.h
LIB = ./libft/libft.a
FLAGS = -Werror -Wextra -Wall -g
SRC = checksum.c \
	creator.c \
	revbytes.c \
	main.c \
	main_loop.c \
	receiver.c \
	roundtrip.c \
	sender.c \
	signals.c \
	x.c

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO) $(HEADER)
	@make -C libft
	gcc $(SRCO) $(LIB) -o $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO)
	@/bin/rm -f compile_commands.json
	@/bin/rm -rf ft_ping.dSYM
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all
