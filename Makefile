# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 04:05:15 by cpak              #+#    #+#              #
#    Updated: 2022/11/23 12:52:09 by cpak             ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:	.cpp .o

SRCS		= test.cpp

OBJS		= $(SRCS:.cpp=.o)

INC			= -I./include

NAME		= test

CC			= c++
CFLAGS		= -Wextra -Wall -Werror -std=c++98

.cpp.o:		$(OBJS)
			${CC} $(CFLAGS) $(INC) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			${CC} $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			clean all

.PHONY:		clean all fclean re
