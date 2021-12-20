# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:54:11 by jvermeer          #+#    #+#              #
#    Updated: 2021/12/20 10:08:06 by jvermeer         ###   ########.fr        #
#    Updated: 2021/12/14 19:30:31 by nschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
	   ./utils/lst_env_utils.c \
	   ./utils/ft_strlen.c \
	   ./utils/ft_isalnum.c \
	   ./utils/ft_strdup.c \
	   ./utils/ft_split.c \
	   ./utils/ft_itoa.c \
	   ./utils/ft_strjoin.c \
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
	   ./builtins/env2.c \
	   ./builtins/exit.c \
	   ./builtins/export.c \
	   ./signals/ft_signal.c\
	   ./utils/create_heredoc.c \
	   ./utils/free_func.c \
	   ./exec/run_cmd.c\
	   ./exec/exec.c\
	   ./exec/exec_utils.c\
	   ./exec/main_utils.c\

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
