NAME = philosopher.a
AR = ar rcs
SRC =	sources/ft_atoi.c\
		sources/printer.c\
		sources/main.c\
		sources/table.c\
		sources/timer.c\
		sources/forks.c\
		sources/room_handler.c\
		sources/ft_isdigit.c\

OBJECT = $(SRC:.c=.o)

HEADERS = ./headers.h


all: $(NAME) $(OBJECT) $(HEADERS)

$(NAME): $(OBJECT) $(HEADERS)
	gcc -Wall -Wextra -Werror $(OBJECT) -o philo_three

%.o: %.c
	gcc -Wall -Wextra -Werror  -I  $(HEADERS) -o $@ -c $< 

clean:
	@rm -f $(OBJECT)

fclean: clean
	@rm -f $(NAME)
	@rm ./philo_three

re: fclean $(NAME)