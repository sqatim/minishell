# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 11:56:08 by oqatim            #+#    #+#              #
#    Updated: 2022/12/04 15:33:25 by sqatim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parse.a

HEADER = minishell.h
OBJ_PATH = Objects
CC = gcc

FLAGS = -Wall -Wextra -Werror 
SRC =	lexer/lexeer.c lexer/lexeer2.c env.c libft/ft_split.c libft/libft_utilis.c quots.c dollar/dollar.c \
		dollar/dollar_utilis2.c dollar/dollar_utilis3.c syntax.c parse/parse.c \
		parse/parse_utilis.c parse/parse_utilis2.c ft_malloc.c
	
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<
	
clean:
	@rm -f $(OBJ) 

fclean: clean
	@rm -f parse.a

re: fclean all