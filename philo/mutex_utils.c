/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:53 by user              #+#    #+#             */
/*   Updated: 2021/11/17 21:57:41 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_init(void)
{
	int	i;

	i = 0;
	while (i < g_info->num_of_phils)
	{
		if (pthread_mutex_init(&g_info->phil[i].fork, NULL) != 0)
			ft_print_error(7);
		i++;
	}
}

void	ft_mutex_destroy(void)
{
	int	i;

	i = 0;
	while (i < g_info->num_of_phils)
	{
		pthread_mutex_destroy(&g_info->phil[i].fork);
		i++;
	}
}

void	ft_mutex_lock(t_ph *phil)
{
	if ((phil->id % 2 != 0) && (phil->id != g_info->num_of_phils))
	{
		pthread_mutex_lock(&(g_info->phil[phil->id].fork));
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
		pthread_mutex_lock(&phil->fork);
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
	}
	else if ((phil->id % 2 != 0) && (phil->id == g_info->num_of_phils))
	{
		pthread_mutex_lock(&phil->fork);
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
		if (g_info->num_of_phils == 1)
			return ;
		pthread_mutex_lock(&(g_info->phil[0].fork));
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
	}
	else
	{
		pthread_mutex_lock(&phil->fork);
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
		pthread_mutex_lock(&(g_info->phil[phil->id].fork));
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
	}
}

void	ft_mutex_unlock(t_ph *phil)
{
	if ((phil->id % 2 != 0) && (phil->id != g_info->num_of_phils))
	{
		pthread_mutex_unlock(&phil->fork);
		pthread_mutex_unlock(&(g_info->phil[phil->id].fork));
	}
	else if ((phil->id % 2 != 0) && (phil->id == g_info->num_of_phils))
	{
		pthread_mutex_unlock(&(g_info->phil[0].fork));
		pthread_mutex_unlock(&phil->fork);
	}
	else
	{
		pthread_mutex_unlock(&(g_info->phil[phil->id].fork));
		pthread_mutex_unlock(&phil->fork);
	}
}
