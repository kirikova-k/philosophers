# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 11:23:22 by ogarthar          #+#    #+#              #
#    Updated: 2021/11/19 14:27:23 by ogarthar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIST =		philo.c\
			philo_utils.c\
			mutex_utils.c\
			philo_actions.c\
			init_philos.c


OBJ = $(LIST:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# COLORS
GREEN = \033[1;32m
RED = \033[1;31m
WHITE = \033[0;37m

all : $(NAME)

	@echo "$(GREEN)philo : ✅ D O N E ✅$(WHITE)"

$(NAME):	$(OBJ) philo.h Makefile
	$(CC) -pthread $(CFLAGS) $(OBJ) -o $(NAME)

re : fclean all

bonus :
	@echo "$(GREEN)nothing to do for bonus. Usage philo_bonus: cd ../philo_bonus -> make bonus -> ./philo_bonus [4 or 5 arguments]$(WHITE)$(WHITE)"

clean :
	rm -f $(OBJ) $(OBJ_B)

fclean : clean
	rm -f $(NAME) $(NAME_B)
	@echo "$(RED)philo: 💣 D E L E T E D 💣$(WHITE)"

.PHONY : all clean fclean re bonus
