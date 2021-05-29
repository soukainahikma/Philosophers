NAME = philosopher.a
AR = ar rcs
SRC =	sources/ft_atoi.c\
		sources/printer.c\
		sources/main.c\
		sources/table.c\
		sources/timer.c\
		sources/forks.c\

OBJECT = $(SRC:.c=.o)

HEADERS = ./headers.h


all: $(NAME)

$(NAME): $(OBJECT) $(HEADERS)
	gcc $(OBJECT) -o philosophers

%.o: %.c
	@gcc  -I  $(HEADERS) -o $@ -c $< 

clean:
	@rm -f $(OBJECT)

fclean: clean
	@rm -f $(NAME) 

re: fclean $(NAME)