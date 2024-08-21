NAME=ft_ls.a
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -I. -Ofast
CFILES= file.c	padding.c	sort.c	utils.c 

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

build/%.o: %.c ft_ls.h
	@mkdir -p build
	@$(CC) $(CFLAGS) $< -o $@

all: $(NAME);

clean:
	@rm -rf build/

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
