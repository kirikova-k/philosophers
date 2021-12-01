/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:19:00 by user              #+#    #+#             */
/*   Updated: 2021/11/19 15:43:14 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_lunches(t_ph *phil)
{
	if (phil->count_eating == g_info->count_lunches)
	{
		g_info->check_lunches++;
		if (g_info->check_lunches == g_info->num_of_phils)
		{
			ft_print_msg(SUCCESS, -1, 0);
			g_exit = 1;
			return ;
		}
	}
	return ;
}

void	ft_eating(t_ph *phil)
{
	phil->time_last_eat = get_current_time_ms();
	ft_print_msg(EATING, get_current_time_ms() - g_info->time_start, \
		phil->id);
	if (g_info->count_lunches > 0)
		phil->count_eating++;
	check_all_lunches(phil);
	ft_usleep(g_info->time_to_eat * 1000);
}

void	ft_sleeping(t_ph *phil)
{
	ft_print_msg(SLEEPING, \
		get_current_time_ms() - g_info->time_start, phil->id);
	ft_usleep(g_info->time_to_sleep * 1000);
}

void	ft_control(void)
{
	int	i;

	i = 0;
	while (1)
	{
		g_info->phil[i].time_without_eat = \
			get_current_time_ms() - g_info->phil[i].time_last_eat;
		if (g_exit == 1)
		{
			ft_mutex_unlock(&g_info->phil[i]);
			return ;
		}
		if ((g_info->phil[i].time_without_eat) >= g_info->time_to_die)
		{
			ft_print_msg(DEATH, (get_current_time_ms() - \
				g_info->time_start), g_info->phil[i].id);
			g_exit = 1;
			ft_mutex_unlock(&g_info->phil[i]);
			return ;
		}
		i++;
		if (i == g_info->num_of_phils - 1)
			i = 0;
	}
}

void	join_philos(void)
{
	int	i;

	i = 0;
	while (i < g_info->num_of_phils)
	{
		while (g_exit == 0)
		{
			if (pthread_join(g_info->phil[i].treads, NULL) != 0)
				ft_print_error(6);
		}
		i++;
	}
	return ;
}
