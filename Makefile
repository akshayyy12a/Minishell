NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -Iincludes -ILibft
LDFLAGS     = -lreadline

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = $(shell find $(SRC_DIR) -name '*.c')
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT       = Libft/libft.a

RM          = rm -f
MKDIR       = mkdir -p

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C Libft

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -C Libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft

re: fclean all

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Lancement de Valgrind sur ./minishell..."
	valgrind -q --suppressions=./ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./minishell

.PHONY: all clean fclean re
