NAME=philo_bonus
SRC = main_bonus.c\
		time_bonus.c\
		utils_bonus.c\

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJ=$(SRC:.c=.o)

all:	$(NAME)

$(NAME) : $(OBJ)
	$(CC) ${CFLAGS} ${OBJ} -o $(NAME)

clean:	
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
 
.PHONY: all clean fclean re