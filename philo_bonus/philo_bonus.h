/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogarthar <ogarthar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:40:41 by ogarthar          #+#    #+#             */
/*   Updated: 2021/11/19 16:24:30 by ogarthar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>

# define FORK		"has taken a fork\n"
# define EATING		"is eating\n"
# define SLEEPING	"is sleeping\n"
# define THINKING	"is thinking\n"
# define DEATH		"is dead, time without eat:"
# define SUCCESS	"all alive, times ate:"

typedef struct s_ph
{
	int				id;
	pid_t			pid;
	long			time_start;
	long			time_last_eat;
	long			time_without_eat;
	int				count_eating;
}t_ph;

typedef struct s_inf
{
	int				num_of_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			time_start;
	long			print_time;
	int				count_lunches;
	int				check_lunches;
	sem_t			*g_sem;
	sem_t			*forks;
	t_ph			*phil;
}t_inf;

t_inf	*g_info;

// mutex_utils.c
void	ft_mutex_init(void);
void	ft_mutex_destroy(void);
void	ft_mutex_lock(t_ph *phil);
void	ft_mutex_unlock(t_ph *phil);

// actions.c
void	*ft_control(void *data);
void	ft_eating(t_ph *phil);
void	ft_sleeping(t_ph *phil);
void	kill_philos(void);
int		check_all_lunches(t_ph *phil);

// philo_utils.c
void	ft_print_msg(char *msg, long time, int id);
long	get_current_time_ms(void);
int		ft_usleep(long time);
char	*ft_strchr(const char *s, int c);

//init_philos.c
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_print_error(int er_no);
int		ft_init(int ac, char **av);
void	ft_get_args(int ac, char **av);

//philo.c
int		ft_one_phil(void);
void	*ft_simulation(void *data);
void	ft_even_thread_create(void);
void	ft_odd_thread_create(void);
int		main(int ac, char **av);

#endif
