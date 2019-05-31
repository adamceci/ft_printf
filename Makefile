NAME = libftprintf.a

SRCS = test.c

all: $(NAME)

$(NAME):

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
