# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 10:06:11 by rleskine          #+#    #+#              #
#    Updated: 2023/04/26 12:02:55 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Use command 'make buf=x all' to compile with -D BUFFER_SIZE=x

NAME	=	get_next_line.o
HDR		=	get_next_line.h
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	$(NAME)

OBJ		=	$(SRC:.c=.o)

CC		=	cc

all: $(NAME)

%.o: %.c
	[ "${buf}" ] && $(CC) $(CFLAGS) -D BUFFER_SIZE=$(buf) -I $(HDR) -c $< -o $@ || $(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean

re: fclean all