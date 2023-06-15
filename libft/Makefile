# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 11:52:06 by rleskine          #+#    #+#              #
#    Updated: 2023/05/02 13:42:42 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
HDR		=	libft.h
CFLAGS	=	-Wall -Wextra -Werror

SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		ft_tolower.c ft_toupper.c ft_ishex.c

OBJ = $(SRC:.c=.o)

LIBS	= libftprintf
OBJS	= get_next_line

INCLIB	= $(foreach lib, $(LIBS), $(lib)/$(lib).a)
INCOBJ	= $(foreach obj, $(OBJS), $(obj)/$(obj).o)

CC = cc

all: $(NAME) 

$(NAME): $(OBJ) $(INCLIB) $(INCOBJ)
	ar rcs $@ $(OBJ) $(INCOBJ)
	ranlib $(NAME)

$(INCLIB):
	$(MAKE) -C $(basename $(notdir $@))
	cat $@ >> $(NAME)

$(INCOBJ):
	$(MAKE) -C $(basename $(notdir $@))

%.o: %.c
	$(CC) $(CFLAGS) -I $(HDR) -c $< -o $@

clean:
	$(foreach lib, $(LIBS), $(MAKE) -C $(lib) clean)
	$(foreach obj, $(OBJS), $(MAKE) -C $(obj) clean)
	/bin/rm -f $(OBJ)

fclean: clean
	$(foreach lib, $(LIBS), $(MAKE) -C $(lib) fclean)
	$(foreach obj, $(OBJS), $(MAKE) -C $(obj) fclean)
	/bin/rm -f $(NAME)

re: fclean all

#.SILENT:
