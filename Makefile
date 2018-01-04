NAME = ft_ls

FLAGS = -ggdb -Wall -Wextra -Werror

SRC = main.c error.c option.c ls.c tree.c stat.c display.c displaytime.c \
		calc_space.c path.c free.c utils.c stat_mode.c

OBJ = $(SRC:.c=.o)

INCLUDE = ./includes/ft_ls.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	gcc $(FLAGS) -c $<

$(NAME): $(OBJ)
	@make -C libft
	gcc -g $(OBJ) -o $(NAME) -I./includes -L libft -lft
	@echo "FT_LS COMPILED"

clean:
	@make clean -C libft
	@rm -rf $(OBJ)
	@echo "OBJECTS DELETED"

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "FT_LS DELETED"

re: fclean all

.PHONY: make re clean fclean
