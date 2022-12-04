NAME= minishell

SRC_PATH= Sources


HDR_PATH= Headers


OBJ_PATH= Objects
LIB_PATH= Libft
PARSE_PATH= Sources/Parse


SRC_NAME=main.c\
	checks.c\
	tools.c\
	builtins.c\
	init.c\
	export.c\
	free.c\
	cd.c\
	builtins_tools.c\
	atoul.c\
	print.c\
	noBuiltins.c\
	noBuiltins_tools.c\
	
	
HDR_NAME=execution.h\

OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

LIB= libft.a
PARSE= parse.a
# FLAGS= -Wall -Wextra -Werror
LLIB_FLAG= -L$(LIB_PATH) Libft/libft.a
LPARSE_FLAG= -L$(PARSE_PATH) Sources/Parse/parse.a

H_FLAG= -I $(HDR_PATH)

COMP= gcc

all: lib parse $(NAME) 

$(NAME) : $(LIB_PATH)/$(LIB) $(PARSE_PATH)/$(PARSE) $(OBJ)
	@rm -rf $(NAME)
	@$(COMP) -g $(H_FLAG) $(OBJ) $(LLIB_FLAG) $(LPARSE_FLAG) -o $(NAME)
	@echo "													 Made by : \033[1;91mqatim && Sqatim\033[m"
	@echo "      ___                       ___                       ___           ___           ___                                  "
	@echo "     /__/\        ___          /__/\        ___          /  /\         /__/\         /  /\                                 "
	@echo "    |  |::\      /  /\         \  \:\      /  /\        /  /:/_        \  \:\       /  /:/_                                "
	@echo "    |  |:|:\    /  /:/          \  \:\    /  /:/       /  /:/ /\        \__\:\     /  /:/ /\    ___     ___   ___     ___  "
	@echo "  __|__|:|\:\  /__/::\      _____\__\:\  /__/::\      /  /:/ /::\   ___ /  /::\   /  /:/ /:/_  /__/\   /  /\ /__/\   /  /\ "
	@echo " /__/::::| \:\ \__\/\:\__  /__/::::::::\ \__\/\:\__  /__/:/ /:/\:\ /__/\  /:/\:\ /__/:/ /:/ /\ \  \:\ /  /:/ \  \:\ /  /:/ "
	@echo " \  \:\~~\__\/    \  \:\/\ \  \:\~~\~~\/    \  \:\/\ \  \:\/:/~/:/ \  \:\/:/__\/ \  \:\/:/ /:/  \  \:\  /:/   \  \:\  /:/  "
	@echo "  \  \:\           \__\::/  \  \:\  ~~~      \__\::/  \  \::/ /:/   \  \::/       \  \::/ /:/    \  \:\/:/     \  \:\/:/   "
	@echo "   \  \:\          /__/:/    \  \:\          /__/:/    \__\/ /:/     \  \:\        \  \:\/:/      \  \::/       \  \::/    "
	@echo "    \  \:\         \__\/      \  \:\         \__\/       /__/:/       \  \:\        \  \::/        \__\/         \__\/     "
	@echo "     \__\/                     \__\/                     \__\/         \__\/         \__\/                                 "
	@echo "						Compilation of $(NAME):  \033[1;32mOK\033[m"

lib:
	@make -sC $(LIB_PATH)

parse:
	@make -sC $(PARSE_PATH)

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) -g $(FLAGS) $(H_FLAG) -g -o $@ -c $<


clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)
	@make clean -C $(PARSE_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(PARSE_PATH)
	@echo "\033[0;31m>> checker & $(NAME) && all obbjects are deleted.\033[0m" 

re : fclean all