NAME = libftprintf.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -c

LIBS = -lft -L$(LIBFT_DIR)
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS)

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_HEADERS = $(LIBFT_DIR)includes/

HEADERS_DIR = ./includes/
HEADERS_LIST = ft_printf.h
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRCS_DIR = ./sources/
SRCS_LIST = ft_printf.c			\
			init.c				\
			modifiers.c			\
			utils.c				\
			flags_priorities.c	\
			fill_struct.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objects/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

# COLORS

NO_COLOR = \x1b[0m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \x1b[33;01m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@cp $(LIBFT) ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(NO_COLOR)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(NO_COLOR)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(NAME): $(GREEN)$(OBJS_DIR) was created$(NO_COLOR)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(NO_COLOR)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(NO_COLOR)"
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "$(NAME): $(RED)$(OBJS_DIR) was deleted$(NO_COLOR)"
	@echo "$(NAME): $(RED)object files were deleted$(NO_COLOR)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(NO_COLOR)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(NO_COLOR)"

re: fclean all
