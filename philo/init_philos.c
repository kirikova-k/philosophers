/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:39:13 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/19 14:55:12 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
	{
		if (!(ft_strchr("0123456789+-", (int)s[len])))
			return (0);
		len++;
	}
	return (len);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;
	int			i;

	sign = 1;
	res = 0;
	i = 0;
	if ((int)ft_strlen(str) > 10 || (int)ft_strlen(str) == 0)
		return (0);
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r' \
	|| str[i] == '\v' || str[i] == ' ' || str[i] == '\f') && (str[i] != '\0'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && (str[i] != '\0'))
	{
		res = (str[i] - '0') + res * 10;
		if ((res > 2147483648 && sign == -1) || (res > 2147483647 && sign == \
		1))
			return (0);
		i++;
	}
	return ((int)res * sign);
}

void	ft_print_error(int er_no)
{
	if (er_no == 1)
		write(1, "need 4 or 5 arguments\n", 22);
	if (er_no == 2)
		write(1, "memory allocation error\n", 24);
	if (er_no == 3)
	{
		if (g_info->num_of_phils < 199)
			er_no = 4;
		else
			write(1, "more 199 philosophers?! are you crazy?!\n", 40);
	}
	if (er_no == 4)
		write(1, "invalid argument\n", 17);
	if (er_no == 5)
		write(1, "error thread create\n", 20);
	if (er_no == 6)
		write(1, "error thread join\n", 18);
	if (er_no == 7)
		write(1, "error mutex init\n", 17);
	if (er_no == 8)
		write(1, "error mutex destroy\n", 20);
	g_exit = 1;
	return ;
}

int	ft_init(int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < g_info->num_of_phils)
	{
		pthread_mutex_init(&g_info->phil[i].fork, NULL);
		g_info->phil[i].id = i + 1;
		g_info->phil[i].count_eating = 0;
	}
	g_info->time_to_die = ft_atoi(av[2]);
	g_info->time_to_eat = ft_atoi(av[3]);
	g_info->time_to_sleep = ft_atoi(av[4]);
	if (g_info->time_to_die < 60 || g_info->time_to_eat < 60 || \
		g_info->time_to_sleep < 60)
		return (1);
	g_info->count_lunches = -1;
	if (ac == 6)
	{
		g_info->count_lunches = ft_atoi(av[5]);
		if (g_info->count_lunches <= 0)
			return (1);
	}
	g_info->time_start = get_current_time_ms();
	g_info->check_lunches = 0;
	return (0);
}

void	ft_get_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_print_error(1);
		return ;
	}
	g_info = (t_inf *)malloc(sizeof(t_inf));
	if (!g_info)
	{
		ft_print_error(2);
		return ;
	}
	g_info->num_of_phils = ft_atoi(av[1]);
	if (g_info->num_of_phils > 199 || g_info->num_of_phils <= 0)
	{
		ft_print_error(3);
		return ;
	}
	g_info->phil = (t_ph *)malloc(sizeof(t_ph) * (g_info->num_of_phils));
	if (!g_info->phil)
	{
		ft_print_error(2);
		return ;
	}
	if (ft_init(ac, av) == 1)
		ft_print_error(4);
}
