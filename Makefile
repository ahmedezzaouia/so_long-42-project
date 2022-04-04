SRCS = so_long.c get_next_line.c get_next_line_utils.c validate_map.c so_long_utils.c so_long_utils2.c
NAME = so_long
LIBFT = ./libft/libft.a
FTPRINTF = ./ft_printf/libftprintf.a
CC = gcc
CFLAGS = -lmlx -framework OpenGl -framework AppKit -g
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	cd libft && make && cd ..
	cd ft_printf && make && cd ..
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(FTPRINTF)  -o $(NAME)

clean:
	cd libft && make clean && cd ..
	rm -f $(OBJS)

fclean:clean
	cd libft && make fclean && cd ..
	rm -f $(NAME)
re: fclean all