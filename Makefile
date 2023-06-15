# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:29:22 by rleskine          #+#    #+#              #
#    Updated: 2023/05/22 14:42:32 by rleskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
SRC			=	readmap.c readmap_utils.c draw_image.c draw_utils.c draw_utils2.c draw_utils3.c fdf_utils.c fdf_hooks.c
OBJ			=	$(SRC:.c=.o)
LIBS		=	./libft/libft.a 
LIBDIR		=	$(basename $(notdir $(LIBS)))
INCLUDE		=	$(addprefix -I, $(LIBDIR)) $(addprefix -L, $(LIBDIR))
LIBFLAGS	=	-lft -lm
CFLAGS		=	-Wall -Wextra -Werror 
# -fsanitize=address
GFX			=	-Imlx -lmlx -framework OpenGL -framework AppKit
NPROCS 		=	$(shell sysctl hw.ncpu | grep -o '[0-9]\+')
#MAKEFLAGS 	+= -j$(NPROCS)

CC =	cc

all: $(LIBS) $(OBJ) $(NAME)

$(NAME): %: %.c
	$(CC) $(CFLAGS) $(GFX) $(INCLUDE) $(LIBFLAGS) -o $@ $< $(OBJ)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBS): %:
	$(MAKE) -j$(NPROCS) -C $(basename $(notdir $@))

clean:
	$(foreach lib, $(LIBDIR), $(MAKE) -C $(lib) clean)
	rm -rf $(OBJ)

fclean: clean
	$(foreach lib, $(LIBDIR), $(MAKE) -C $(lib) fclean)
	/bin/rm -f $(NAME)

re: fclean all

#.SILENT:
