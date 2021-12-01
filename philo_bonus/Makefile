# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 11:23:22 by ogarthar          #+#    #+#              #
#    Updated: 2021/11/19 14:26:52 by ogarthar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_B = philo_bonus

LIST_B =	philo_bonus.c\
			philo_utils_bonus.c\
			philo_actions_bonus.c\
			init_philos_bonus.c

OBJ_B = $(LIST_B:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# COLORS
GREEN = \033[1;32m
RED = \033[1;31m
WHITE = \033[0;37m

all :

	@echo "$(GREEN)nothing to do for all. Usage philo: cd ../philo -> make -> ./philo [4 or 5 arguments]$(WHITE)"

re : fclean all

bonus : $(NAME_B)  philo_bonus.h Makefile

	@echo "$(GREEN)philo_bonus : ✅ D O N E ✅$(WHITE)"

$(NAME_B):	$(OBJ_B) philo_bonus.h Makefile
	$(CC) -pthread $(CFLAGS) $(OBJ_B) -o $(NAME_B)

clean :
	rm -f $(OBJ) $(OBJ_B)

fclean : clean
	rm -f $(NAME) $(NAME_B)
	@echo "$(RED)philo_bonus: 💣 D E L E T E D 💣$(WHITE)"

.PHONY : all clean fclean re bonus
