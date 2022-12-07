NAME = minishell

HEADER = minishell.h

CC = gcc

FLAGS = -Wall -Wextra -Werror 
SRC =Sources/Parse/lexer/lexeer.c\
	Sources/Parse/lexer/lexeer2.c\
	Sources/Parse/env.c \
	Sources/Parse/libft/ft_split.c\
	Sources/Parse/libft/libft_utilis.c\
	Sources/Parse/quots.c \
	Sources/Parse/dollar/dollar.c\
	Sources/Parse/dollar/dollar_utilis2.c\
	Sources/Parse/dollar/dollar_utilis3.c\
	Sources/Parse/syntax.c\
	Sources/Parse/parse/parse.c\
	Sources/Parse/parse/parse_utilis.c\
	Sources/Parse/parse/parse_utilis2.c\
	Sources/Parse/ft_malloc.c\
	Sources/main.c\
	Sources/checks.c\
	Sources/tools.c\
	Sources/builtins.c\
	Sources/init.c\
	Sources/export.c\
	Sources/free.c\
	Sources/cd.c\
	Sources/builtins_tools.c\
	Sources/atoul.c\
	Sources/print.c\
	Sources/noBuiltins.c\
	Sources/noBuiltins_tools.c\
	
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ)  -o $(NAME)

clean:
	@rm -f $(OBJ) 

fclean: clean
	@rm -f minishell

re: fclean all