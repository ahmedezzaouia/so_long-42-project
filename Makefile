SRCS = so_long.c get_next_line.c get_next_line_utils.c validate_map.c
NAME = so_long
LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -lmlx -framework OpenGl -framework AppKit -g

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(SRCS)
	cd libft && make && cd ..
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT)  -o $(NAME)

clean:
	cd libft && make clean && cd ..
	rm -f $(OBJS)

fclean:clean
	cd libft && make fclean && cd ..
	rm -f $(NAME)
re: fclean all