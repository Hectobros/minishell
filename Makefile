# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:54:11 by jvermeer          #+#    #+#              #
#    Updated: 2021/12/08 18:15:25 by jvermeer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	   check_open_quotes.c \
	   ft_strlen.c \

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -pthread # -g -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(CFLAGS) $(OBJS) -lreadline

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all
