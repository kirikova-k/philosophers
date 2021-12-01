/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:58:37 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/19 16:20:41 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_one_phil(void)
{
	if (g_info->num_of_phils == 1)
	{
		printf("%d 1 is dead\n", (g_info->time_to_die));
		exit (0);
	}
	return (0);
}

void	*ft_simulation(void *data)
{
	pthread_t	t_control;
	t_ph		*phil;

	phil = (t_ph *)data;
	pthread_create(&t_control, NULL, ft_control, \
			(void *)phil);
	phil->time_start = get_current_time_ms();
	phil->time_last_eat = get_current_time_ms();
	phil->time_without_eat = get_current_time_ms() - phil->time_last_eat;
	while (1)
	{
		sem_wait(g_info->forks);
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
		ft_print_msg(FORK, get_current_time_ms() - phil->time_start, phil->id);
		ft_eating(phil);
		sem_post(g_info->forks);
		ft_sleeping(phil);
		ft_print_msg(THINKING, get_current_time_ms() - \
			g_info->time_start, phil->id);
	}
	return (NULL);
}

void	ft_odd_process_create(void)
{
	int	i;

	i = 0;
	while (i < g_info->num_of_phils)
	{
		g_info->phil[i].pid = fork();
		if (g_info->phil[i].pid == 0)
			ft_simulation((void *)&g_info->phil[i]);
		i = i + 2;
	}
}

void	ft_even_process_create(void)
{
	int	i;

	i = 1;
	while (i < g_info->num_of_phils)
	{
		g_info->phil[i].pid = fork();
		if (g_info->phil[i].pid == 0)
			ft_simulation((void *)&g_info->phil[i]);
		i = i + 2;
	}
}

int	main(int ac, char **av)
{
	ft_get_args(ac, av);
	sem_unlink("forks");
	sem_unlink("msg");
	g_info->g_sem = sem_open("msg", O_CREAT, S_IRWXU, 1);
	g_info->forks = sem_open("forks", O_CREAT, S_IRWXU, \
		g_info->num_of_phils / 2);
	ft_odd_process_create();
	ft_even_process_create();
	waitpid(-1, NULL, 0);
	kill_philos();
	sem_close(g_info->forks);
	sem_close(g_info->g_sem);
	sem_unlink("forks");
	sem_unlink("msg");
	free(g_info->phil);
	free(g_info);
	return (0);
}
