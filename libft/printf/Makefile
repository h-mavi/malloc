# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfanelli <mfanelli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 17:51:13 by mfanelli          #+#    #+#              #
#    Updated: 2026/02/09 14:09:06 by mfanelli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCES = ft_printf.c ft_putchar.c ft_putint.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

$(NAME) : $(OBJECTS) libft
	@echo "Compiling library $(NAME)"
	cp ../libft.a $(NAME)
	ar -rcs $(NAME) $(OBJECTS)

libft :
	@echo "Compiling libft"
	cd .. && make
	
test : libft
	@echo "Compiling test $(NAME)"
	$(CC) $(CFLAGS) $(SOURCES) ../libft.a -o printf

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<
	
clean :
	rm -f $(OBJECTS)
	cd .. && make clean
fclean : clean
	rm -f $(NAME)
	rm -f printf
	cd .. && make fclean

all : $(NAME)

re : fclean all

.PHONY: all test clean fclean re
.SILENT: