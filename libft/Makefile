# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/26 11:41:06 by nschmitt          #+#    #+#              #
#    Updated: 2021/11/20 19:53:04 by nschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFTDIR = minilib

CFLAGS = -Wall -Werror -Wextra

OBJLIB = ./minilib/ft_memset.o ./minilib/ft_bzero.o ./minilib/ft_memcpy.o ./minilib/ft_memccpy.o \
        ./minilib/ft_memmove.o ./minilib/ft_memchr.o ./minilib/ft_memcmp.o ./minilib/ft_strlen.o \
        ./minilib/ft_isalpha.o ./minilib/ft_isdigit.o ./minilib/ft_isalnum.o ./minilib/ft_isascii.o \
        ./minilib/ft_isprint.o ./minilib/ft_toupper.o ./minilib/ft_tolower.o ./minilib/ft_strchr.o \
        ./minilib/ft_strrchr.o ./minilib/ft_strncmp.o ./minilib/ft_strlcpy.o ./minilib/ft_strlcat.o \
        ./minilib/ft_strnstr.o ./minilib/ft_atoi.o ./minilib/ft_calloc.o ./minilib/ft_strdup.o \
        ./minilib/ft_substr.o ./minilib/ft_strjoin.o ./minilib/ft_strtrim.o ./minilib/ft_split.o \
        ./minilib/ft_itoa.o ./minilib/ft_strmapi.o ./minilib/ft_putchar_fd.o \
        ./minilib/ft_putstr_fd.o ./minilib/ft_putendl_fd.o ./minilib/ft_putnbr_fd.o \
		./minilib/ft_ternaire.o

SRCS = ./ft_printf.c ./ft_read.c ./dconv.c ./ft_putchar.c ./ft_sconv.c ./cconv.c \
		./ft_pourconv.c ./ft_putnbrbase.c ./ft_pconv.c ./ft_putstrspe.c ./ft_xconv.c \
		./extra.c

OBJ = ./ft_printf.o ./ft_read.o ./dconv.o ./ft_putchar.o ./ft_sconv.o ./cconv.o \
		./ft_pourconv.o ./ft_putnbrbase.o ./ft_pconv.o ./ft_putstrspe.o ./ft_xconv.o \
		./extra.o

all: $(NAME)

$(NAME) :
	make -C $(LIBFTDIR)
	gcc -c $(CFLAGS) $(SRCS)
	ar rc $(NAME) $(OBJLIB) $(OBJ)
	ranlib $(NAME)

libftclean:
	make clean -C $(LIBFTDIR)
libftfclean:
	make fclean -C $(LIBFTDIR)
clean: libftclean
	rm -f $(OBJ)
fclean: clean libftfclean
	rm -f $(NAME)
re: fclean all

.PHONY: clean fclean all re libftfclean libftclean