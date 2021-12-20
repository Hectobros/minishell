# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:54:11 by jvermeer          #+#    #+#              #
#    Updated: 2021/12/19 17:20:21 by jvermeer         ###   ########.fr        #
#    Updated: 2021/12/14 19:30:31 by nschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	   ./libftfiles/ft_strlen.c \
	   ./libftfiles/ft_isalnum.c \
	   ./libftfiles/ft_strdup.c \
	   ./libftfiles/ft_split.c \
	   ./libftfiles/ft_itoa.c \
	   ./libftfiles/ft_strjoin.c \
	   ./lexer/check_quotes.c \
	   ./lexer/split_content.c \
	   ./lexer/lst_content_utils.c \
	   ./lexer/utils_lex.c \
	   ./lexer/dol_is.c \
	   ./lexer/replace_env.c \
	   ./lexer/make_token.c \
	   ./ns/ft_lstnewmini.c \
	   ./ns/ft_memmoven.c \
	   ./ns/ft_parsing.c \
	   ./ns/ft_strdupn.c \
	   ./ns/ft_lstlastm.c \
	   ./ns/ft_lstadd_backmini.c \
	   ./ns/ft_parsdeux.c \
	   ./ns/ft_openner.c \
	   ./ns/parsutils.c \
	   ./builtins/cd_pwd.c \
	   ./builtins/echo.c \
	   ./builtins/env.c \
	   ./builtins/exit.c \
	   ./builtins/envdeux.c \
	   ./builtins/envutilstest.c \
	   ./signals/ft_signal.c\
	   create_heredoc.c \
	   lst_env_utils.c \
	   free_func.c \

OBJS = ${SRCS:.c=.o}

CFLAGS = -fPIE -Wall -Wextra -Werror -pthread# -g -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(CFLAGS) $(OBJS) -lreadline

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all
