# Variables
NAME = libftprintf.a


SRCS = ft_printf.c ft_putchar.c ft_puthexnbr.c ft_puthexnbrmaj.c ft_putnbr.c ft_putpointer.c ft_putposnbr.c ft_putstr.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) 
	@echo "Object files removed."

fclean: clean
	$(RM) $(NAME)

re: fclean all