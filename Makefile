NAME = pipex
CFLAGS = -Wall -Werror -Wextra
SRC = src/utils.c src/error_handling.c src/path_handling.c src/pipex.c
LIBFT = libft
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L./$(LIBFT) -lft -o $(NAME)

clean:
	rm -rf $(LIBFT)/*.o
	rm -rf $(OBJS)

fclean: clean
	rm -f $(LIBFT)/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re