# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 12:25:23 by nschmitt          #+#    #+#              #
#    Updated: 2021/12/07 14:41:12 by nschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR = ./src/libft 

NAME = minishell

SRC = ./src/minishell.c

OBJ = ./src/minishell.o

CC = cc

CFLAGS = -Wall -Wextra -Werror

CSUPP = -lreadline

RM = rm -f

all: LIB CRR

LIB : 
	make -C ${LIBFTDIR}

CRR : ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${CFLAGS} ./src/libft/libftprintf.a ${CSUPP}

libftclean:
	make clean -C ${LIBFTDIR}

libftfclean:
	make fclean -C ${LIBFTDIR}

clean: libftclean
	${RM} ${OBJ}

fclean: clean libftfclean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean all libftclean libftfclean
