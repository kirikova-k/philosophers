/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:58:37 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/18 19:35:02 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_one_phil(void)
{
	if (g_info->num_of_phils == 1)
	{
		printf("%d 1 is dead\n", (g_info->time_to_die));
		g_exit = 1;
		return (1);
	}
	return (0);
}

void	*ft_simulation(void *data)
{
	t_ph	*phil;

	phil = (t_ph *)data;
	phil->time_start = get_current_time_ms();
	phil->time_last_eat = get_current_time_ms();
	phil->time_without_eat = get_current_time_ms() - phil->time_last_eat;
	while (1)
	{
		ft_mutex_lock(phil);
		if (ft_one_phil() == 1)
		{
			ft_mutex_unlock(phil);
			return (NULL);
		}
		ft_eating(phil);
		ft_mutex_unlock(phil);
		ft_sleeping(phil);
		ft_print_msg(THINKING, get_current_time_ms() - \
			g_info->time_start, phil->id);
	}
	return (NULL);
}

void	ft_odd_thread_create(void)
{
	int	i;

	i = 0;
	while (i < g_info->num_of_phils)
	{
		if (pthread_create(&(g_info->phil[i].treads), NULL, ft_simulation, \
			(void *)&g_info->phil[i]) != 0)
			ft_print_error(5);
		usleep(500);
		i = i + 2;
	}
}

void	ft_even_thread_create(void)
{
	int	i;

	i = 1;
	while (i < g_info->num_of_phils)
	{
		if (pthread_create(&(g_info->phil[i].treads), NULL, ft_simulation, \
			(void *)&g_info->phil[i]) != 0)
			ft_print_error(5);
		usleep(500);
		i = i + 2;
	}
}

int	main(int ac, char **av)
{
	g_exit = 0;
	ft_get_args(ac, av);
	if (g_exit == 1)
		return (0);
	pthread_mutex_init(&g_info->g_mutex, NULL);
	ft_mutex_init();
	ft_odd_thread_create();
	ft_even_thread_create();
	ft_control();
	join_philos();
	ft_mutex_destroy();
	pthread_mutex_destroy(&g_info->g_mutex);
	free(g_info->phil);
	free(g_info);
	return (0);
}
