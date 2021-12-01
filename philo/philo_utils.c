/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:58:24 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/19 16:21:41 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_msg(char *msg, long time, int id)
{
	pthread_mutex_lock(&g_info->g_mutex);
	if (msg[3] == 'd')
	{
		printf("%ld %d %s %ld \n", time, id, msg, g_info->phil[id - \
			1].time_without_eat);
		return ;
	}
	else if (time != -1 && id > 0)
		printf("%ld %d %s", time, id, msg);
	else if (time == -1)
	{
		printf("%s %d \n", msg, g_info->count_lunches);
		return ;
	}
	pthread_mutex_unlock(&g_info->g_mutex);
}

long	get_current_time_ms(void)
{
	struct timeval	t;
	long			time_ms;

	gettimeofday(&t, NULL);
	time_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000) + 1000;
	return (time_ms);
}

int	ft_usleep(long time)
{
	struct timeval	start;
	struct timeval	new;

	if (gettimeofday(&start, NULL) == -1)
		return (1);
	while (g_exit != 1)
	{
		usleep(20);
		if (gettimeofday(&new, NULL))
			return (1);
		if ((long)((new.tv_sec - start.tv_sec) * 1000000
			+ new.tv_usec - start.tv_usec) > (long)time)
			break ;
		if (g_exit == 1)
			break ;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
