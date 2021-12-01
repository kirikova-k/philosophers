/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:19:00 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/19 16:24:38 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_all_lunches(t_ph *phil)
{
	if (phil->count_eating == g_info->count_lunches)
	{
		g_info->check_lunches++;
		if (g_info->check_lunches == g_info->num_of_phils)
		{
			ft_print_msg(SUCCESS, -1, 0);
			return (1);
		}
	}
	return (0);
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

void	*ft_control(void *data)
{
	t_ph	*phil;

	phil = (t_ph *)data;
	while (1)
	{
		phil->time_without_eat = \
			get_current_time_ms() - phil->time_last_eat;
		if (check_all_lunches(phil) == 1)
			exit (0);
		if ((phil->time_without_eat) >= g_info->time_to_die)
		{
			ft_print_msg(DEATH, (get_current_time_ms() - \
				g_info->time_start), phil->id);
			exit (0);
			sem_post(g_info->forks);
			return (NULL);
		}
	}
}

void	kill_philos(void)
{
	int	i;

	i = 0;
	while (i < g_info->num_of_phils)
	{
		kill(g_info->phil[i].pid, SIGTERM);
		i++;
	}
	return ;
}
