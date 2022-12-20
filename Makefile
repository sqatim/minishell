NAME = minishell

HEADER = Headers/minishell.h

LIB_PATH= Libft

INCLUDE_READLINE = $(addprefix $(READLINE_PATH),/include)

LIB_READLINE = $(addprefix $(READLINE_PATH),/lib)

READLINE_PATH = $(shell brew --prefix readline)

LLIB_FLAG= -L$(LIB_PATH) Libft/libft.a


LIB= libft.a

CC = gcc

# FLAGS = -Wall -Wextra -Werror 
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
	Sources/signalHandler.c\
	Sources/parseCustomized.c\
	Sources/redirections.c\
	Sources/redirections_tools.c\
	Sources/exec.c\
	Sources/exec_tools.c\
	Sources/clone.c\
	
OBJ = $(SRC:%.c=%.o)

all: lib $(NAME)

$(NAME) : $(LIB_PATH)/$(LIB) $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) $(LLIB_FLAG) -o $(NAME) -lreadline
	# $(CC) $(FLAGS) $(OBJ) $(LLIB_FLAG) -I $(INCLUDE_READLINE) -L$(LIB_READLINE) -o $(NAME) -lreadline

lib:
	@make -sC $(LIB_PATH)


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make clean -sC $(LIB_PATH)
	@rm -f $(OBJ) 

fclean: clean
	@rm -rf $(LIB_PATH)/libft.a
	@rm -f minishell

re: fclean all