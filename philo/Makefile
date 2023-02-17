NAME=philo
SRC = main.c\
		more_utils.c\
		time.c\
		utils.c\

CC = cc

CFLAGS = -Wall -Wextra -Werror #-pthread -fsanitize=thread -g

OBJ=$(SRC:.c=.o)

all:	$(NAME)

$(NAME) : $(OBJ)
	$(CC) ${CFLAGS} ${OBJ}   -o $(NAME)

clean:	
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
 
.PHONY: all clean fclean re