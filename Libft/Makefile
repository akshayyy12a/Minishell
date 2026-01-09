# Variables
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
      ft_strtrim.c ft_split.c ft_itoa.c ft_striteri.c ft_strcpy.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
      ft_strrchr.c ft_strmapi.c ft_strcmp.c get_next_line.c \
      ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_putpointer.c ft_printf/ft_putposnbr.c \
      ft_printf/ft_puthexnbr.c ft_printf/ft_puthexnbrmaj.c ft_printf/ft_putnbr.c ft_printf/ft_putstr.c \

SRCBONUS = ft_lstmap.c ft_lstnew.c ft_lstiter.c \
		ft_lstlast.c ft_lstsize.c ft_lstclear.c \
		ft_lstdelone.c ft_lstadd_back.c ft_lstadd_front.c \

OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)
RM = rm -f
EXEC = main

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

$(EXEC): $(NAME) main.c
	@echo "Compilation de l'exécutable $(EXEC)..."
	$(CC) $(CFLAGS) main.c -L. -lft -o $(EXEC)
	@echo "Exécutable $(EXEC) créé avec succès.""

bonus: $(OBJ) $(OBJBONUS)
	@ar	rcs $(NAME) $(OBJ) $(OBJBONUS)
	@echo "Library $(NAME) with bonus created."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(RM) $(OBJ) $(OBJBONUS)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME) $(RM) $(EXEC)
	@echo "Library $(NAME) removed."

re: fclean all

.PHONY: all clean fclean re bonus
