CC = gcc

RM = rm -f

NAME = lemipc

SRC =  main.c \
			 player.c \
			 sem.c \
			 position.c \
			 map.c \
			 strtowordtab.c \
			 play.c \
			 check.c \
			 algo.c \
			 lib.c \
			 display.c

CFLAGS = -W -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

CFLAGS += -I./include

all: $(NAME)

$(NAME): $(OBJ)
				$(CC) -o $(NAME) $(OBJ) $(FLAGS)
				make -C bonus/

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJBONUS)
	make clean -C bonus/

fclean: clean
		$(RM) $(NAME)
		make fclean -C bonus/

re: fclean all

.PHONY: all clean fclean re
