/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:06:24 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/18 01:10:53 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	struct s_superv	*superv;
}					t_philo;

typedef struct s_superv
{
	int				dead_flag;
	t_philo			*philos;
	pthread_t		mutex_check_forks;
}					t_superv;

long	ft_atol(const char *str);
void	check_av(char **av);
void	check_args(int ac, char **av);
size_t	ft_strlen(const char *s);
void 	ll_check(char *av);
int		init_philos(t_superv *superv, char **av, int ac);
size_t get_current_time_in_ms(void);
void check_eating_times(t_superv *superv, char **av, int ac);
void *philo_routine(void *philo);
void thread_creation(t_superv *superv);
int philo_eats(t_philo *philo);
int philo_sleeps(t_philo *philo);
void forks(t_superv *superv, int i);
void *are_forks_locked(void *philo);


#endif


