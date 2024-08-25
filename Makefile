NAME = pipex
CFLAGS = -Wall -Werror -Wextra
SRC = src/pipex.c src/utils.c
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $() $(NAME)