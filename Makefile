# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:54:11 by jvermeer          #+#    #+#              #
#    Updated: 2021/12/13 18:07:38 by jvermeer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	   ft_strlen.c \
	   ft_isalnum.c \
	   ft_strdup.c \
	   check_quotes.c \
	   split_content.c \
	   create_heredoc.c \
	   lst_content_utils.c \

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -pthread# -g -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(CFLAGS) $(OBJS) -lreadline

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all
