# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/25 13:47:03 by mbenjell          #+#    #+#              #
#    Updated: 2017/07/16 11:28:28 by mbenjell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	fractol

SRC = 	fractol.c \
		draw.c \
		calculus.c \
		events.c \
		ft_strcmp.c \

LIBMLX = ./minilibx/libmlx.a -framework OpenGL -framework AppKit

FLAG = -Wall -Werror -Wextra

RM = /bin/rm -f

OBJ = $(addsuffix .o,$(basename $(SRC)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		@make -C minilibx
		@gcc $(FLAG) $(SRC) -o $(NAME) $(LIBFT) $(LIBMLX)

clean:
		@$(RM) $(OBJ)
fclean:	clean
		@$(RM) $(NAME)
re:		fclean all
