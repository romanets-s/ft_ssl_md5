NAME = ft_ssl
SRC = main.c md5.c md5_part_2.c sha256.c sha256_part_2.c ft_itoa_base.c\
get_input.c
SRCO = $(SRC:.c=.o)
INCLUDES = md5.h sha256.h ft_ssl.h

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SRCO)
	@make -C libft
	@gcc $(FLAGS) -o $(NAME) $(SRCO) $(LIBFT) $(PRINTF)
	@echo "\033[32;1m<ft_ssl>   | done"

.c.o:
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(SRCO)
	@make clean -C libft
	@echo "\033[32;1m<ft_ssl>   | clean succes"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "\033[32;1m<ft_ssl>   | fclean succes"

re: fclean all
	@echo "\033[32;1m<ft_ssl>   | re succes"
