# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 11:56:08 by oqatim            #+#    #+#              #
#    Updated: 2023/01/19 02:03:25 by oqatim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparse.a

HEADER = ../../Headers/minishell.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror 
SRC =	lexer/lexeer.c lexer/lexeer2.c lexer/lexeer3.c lexer/lexeer4.c libft/libft_utilis.c quots.c dollar/dollar.c \
		dollar/dollar_utilis2.c dollar/dollar_utilis3.c dollar/dollar_utilis4.c syntax.c parse/parse.c \
		parse/parse_utilis.c parse/parse_utilis2.c quots_h.c dollar/dollar_hair.c
	
OBJ = $(SRC:%.c=%.o)



all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	# $(CC) $(FLAGS) $(OBJ) -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)


clean:
	@rm -f $(OBJ) 

fclean: clean
	@rm -f $(NAME)

re: fclean all