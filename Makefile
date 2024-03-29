NAME = minishell

HEADER = Headers/minishell.h

LIB_PATH= Libft
PARSE_PATH= Sources/Parse

INCLUDE_READLINE = $(addprefix $(READLINE_PATH),/include)

LIB_READLINE = $(addprefix $(READLINE_PATH),/lib)

READLINE_PATH = $(shell brew --prefix readline)

LLIB_FLAG= -L$(LIB_PATH) Libft/libft.a
LPARSE_FLAG= -L$(PARSE_PATH) Sources/Parse/libparse.a


LIB= libft.a
PARSE= libparse.a

CC = gcc

FLAGS = -Wall -Wextra -Werror 
SRC =Sources/main.c\
	Sources/checks.c\
	Sources/tools.c\
	Sources/builtins.c\
	Sources/builtins2.c\
	Sources/init.c\
	Sources/init2.c\
	Sources/export.c\
	Sources/unset.c\
	Sources/free.c\
	Sources/free2.c\
	Sources/cd.c\
	Sources/builtins_tools.c\
	Sources/atoul.c\
	Sources/print.c\
	Sources/print2.c\
	Sources/noBuiltins.c\
	Sources/noBuiltins_tools.c\
	Sources/signalHandler.c\
	Sources/redirections.c\
	Sources/redirections_tools.c\
	Sources/redirections_tools2.c\
	Sources/exec.c\
	Sources/exec_tools.c\
	Sources/clone.c\
	Sources/tools2.c\
	
OBJ = $(SRC:%.c=%.o)

all: lib parse $(NAME)

$(NAME) : $(LIB_PATH)/$(LIB) $(PARSE_PATH)/$(PARSE) $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) $(LLIB_FLAG) $(LPARSE_FLAG) -lreadline -I $(INCLUDE_READLINE) -L$(LIB_READLINE) -o $(NAME) 

lib:
	@make -sC $(LIB_PATH)

parse:
	@make -sC $(PARSE_PATH)

%.o: %.c
	$(CC) $(FLAGS) -I $(INCLUDE_READLINE) -c $< -o $@

clean:
	@make clean -sC $(LIB_PATH)
	@make clean -sC $(PARSE_PATH)
	@rm -f $(OBJ) 

fclean: clean
	@rm -rf $(LIB_PATH)/libft.a
	@rm -rf $(PARSE_PATH)/libparse.a
	@rm -f minishell

re: fclean all