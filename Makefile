# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 16:45:50 by kben-ham          #+#    #+#              #
#    Updated: 2023/04/01 21:51:49 by kben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

RM = rm -rf

MY_FILES = philo.c try.c initialize.c

OBJECT = $(MY_FILES:.c=.o)

all: $(NAME)

%.o: %.c philo.h
	$(CC)  $(CFLAGS) -o $@ -c  $<

$(NAME): $(OBJECT)
	$(CC)  $(CFLAGS) $^ -o $(NAME)

clean:
	@$(RM) $(OBJECT)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
