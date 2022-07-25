# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 15:07:42 by alsanche          #+#    #+#              #
#    Updated: 2022/07/25 12:42:41 by alsanche         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c base_fts/ft_cd.c env.c\
	base_fts/ft_echo.c read_line.c \
	env_2_str.c export.c

OBJS = $(SRC:.c=.o)

CC = gcc

DEBUG = -fsanitize=address -g3

CFLAGS = -Wall -Werror -Wextra
#CFLAGS += $(DEBUG)

all:  $(NAME)

$(NAME): $(OBJS)
		make -sC libft
		$(CC) $^ -o $@ $(CFLAGS) -lreadline ./libft/libft.a

clean:
	@	make fclean -sC libft
	@	rm -rf ./ft_cd/$(OBJS)
	@	rm -rf $(OBJS)

fclean:
	@	make clean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean