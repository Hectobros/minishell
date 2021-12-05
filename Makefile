# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/26 12:25:23 by nschmitt          #+#    #+#              #
#    Updated: 2021/12/05 11:56:17 by nschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR = libft 

NAME = minishell

SRC = main.c

OBJ = main.o

CC = cc

CFLAGS = -Wall -Wextra -Werror

CSUPP = -lreadline

RM = rm -f

all: LIB CRR

LIB : 
	make -C ${LIBFTDIR}

CRR : ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${CFLAGS} ./libft/libftprintf.a ${CSUPP}

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
