# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 11:52:06 by rleskine          #+#    #+#              #
#    Updated: 2023/04/26 11:46:47 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
HDR		=	./libft
CFLAGS	=	-Wall -Wextra -Werror 
# -fsanitize=address

SRC =	ft_printf.c ft_printf_utils1.c ft_printf_utils2.c ft_printf_utils3.c ft_printf_utils4.c ft_printf_convert1.c

BONUS_NAME =	libftprintf_bonus.a
BONUS_SRC =	ft_printf_bonus.c ft_printf_utils1_bonus.c ft_printf_utils2_bonus.c ft_printf_utils3_bonus.c \
ft_printf_utils4_bonus.c ft_printf_convert1_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ =	$(BONUS_SRC:.c=.o)

CC = cc

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^ 
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HDR) -c $< -o $@

clean:
	/bin/rm -f $(OBJ) $(BONUS_OBJ) $(LIB).a

fclean: clean
	/bin/rm -f $(NAME) $(BONUS_NAME)

re: fclean all