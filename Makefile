# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 15:07:42 by alsanche          #+#    #+#              #
#    Updated: 2022/07/27 21:21:04 by alsanche         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c base_fts/ft_cd.c env/env.c \
	base_fts/ft_echo.c read_line.c \
	env/env_2_str.c env/get_env_value.c \
	export.c ft_puterror.c base_fts/ft_pwd.c

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
	@	make clean -sC libft
	@	rm -rf $(OBJS)

fclean:
	@	make clean
	@	make fclean -sC libft
	@	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean