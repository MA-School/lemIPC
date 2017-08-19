CC = gcc

RM = rm -f

NAME = Graphic

SRC =  displaySFML.c \
			 ../sem.c

CFLAGS = -W -Wall -Wextra

OBJ = $(SRC:.c=.o)

CFLAGS += -I./../include

all: $(NAME)

$(NAME): $(OBJ)
				$(CC) -o $(NAME) $(OBJ) $(FLAGS) -lpthread -lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system
				mv $(NAME) ../

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJBONUS)

fclean: clean
		$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
