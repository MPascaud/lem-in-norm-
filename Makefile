# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 20:57:47 by mpascaud          #+#    #+#              #
#    Updated: 2018/05/09 16:52:43 by mpascaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in.a

TAGS = -Wall -Werror -Wextra

SRC = get_next_line.c ft_strnew.c ft_strlen.c ft_strncat.c ft_strcpy.c ft_isdigit.c ft_strstr.c ft_strcmp.c ft_atoi.c

BIN = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@ gcc $(TAGS) -c $(SRC)
	@ ar rc $(NAME) $(BIN)
	@ ranlib $(NAME)
	@ gcc -fsanitize=address -o lem-in lem-in.c lem-in.a

clean:
	@ rm -rf $(BIN) lem-in.o

fclean: clean
	@ rm -rf $(NAME)
	@ rm -rf lem-in

re: fclean all


.PHONY: all clean fclean re
