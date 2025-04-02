# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 08:45:37 by vfidelis          #+#    #+#              #
#    Updated: 2025/03/26 11:20:56 by vfidelis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
LIB = philo_lib.a
LIB_CREATE = ar -rcs
REMOVE_FILES = rm -rf
COMP = cc
FLAGS = -Wall -Werror -Wextra

FILE_C = ft_initialize.c useful.c useful2.c philo_cycle.c monitoring.c one_philo.c main.c
FILE_O = $(FILE_C:.c=.o)

all: $(NAME)

$(LIB): $(FILE_O)
	$(LIB_CREATE) $(LIB) $(FILE_O)

.c.o:
	$(COMP) $(FLAGS) -c $< -o $(<:.c=.o) -g

$(NAME): $(LIB)
	$(COMP) $(FLAGS) $(LIB) -o $(NAME) -g

clean:
	$(REMOVE_FILES) $(FILE_O)

fclean: clean
	$(REMOVE_FILES) $(LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re
