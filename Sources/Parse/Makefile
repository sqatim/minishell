# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 11:56:08 by oqatim            #+#    #+#              #
#    Updated: 2023/01/09 13:14:31 by samirqatim       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparse.a

HEADER = ../../Headers/minishell.h

CC = gcc

FLAGS = -Wall -Wextra -Werror 
SRC =	lexer/lexeer.c lexer/lexeer2.c lexer/lexeer3.c env.c libft/ft_split.c libft/libft_utilis.c quots.c dollar/dollar.c \
		dollar/dollar_utilis2.c dollar/dollar_utilis3.c dollar/dollar_hair.c syntax.c parse/parse.c \
		parse/parse_utilis.c parse/parse_utilis2.c ft_malloc.c quots_h.c \
	
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