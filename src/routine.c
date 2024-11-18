/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:47 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/18 01:20:10 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thread_creation(t_superv *superv)
{
	int i;

	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		pthread_create(&superv->philos[i].thread, NULL, &philo_routine, &superv->philos[i]);
		pthread_create(&superv->mutex_check_forks, NULL, &are_forks_locked,&superv->philos[i]); // queria mudar para ser so 1
		i++;
	}
	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		pthread_join(superv->philos[i].thread, NULL);
		i++;
	}
}

void *philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (ph->num_times_to_eat != -1 && ph->meals_eaten >= ph->num_times_to_eat)
			return (NULL);
		
		philo_eats(ph);
		philo_sleeps(ph);
		if (ph->num_times_to_eat != -1 && ph->meals_eaten >= ph->num_times_to_eat)
			return (NULL);
		if (get_current_time_in_ms() - (ph->start_time + ph->last_meal) > ph->time_to_die)
		{
			printf("%ld %d died\n", get_current_time_in_ms() - ph->start_time ,ph->id);
			*ph->dead = 1;
			return (NULL);
		}
	}
	return (NULL);
}
int philo_sleeps(t_philo *philo)
{
	size_t time;

	time = get_current_time_in_ms();
	if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
		return (0);
	printf("%ld %d is sleeping\n", time - philo->start_time ,philo->id);
	while(philo->time_to_sleep < get_current_time_in_ms() - time)
	{
		if (get_current_time_in_ms() - (philo->start_time + philo->last_meal) > philo->time_to_die)
		{
			printf("%ld %d died\n", get_current_time_in_ms() - philo->start_time ,philo->id);
			*philo->dead = 1;
			return (1);
		}
		usleep(philo->time_to_sleep * 10);
	}
	if(are_forks_locked(philo))
		printf("%ld %d is thinking\n", time - philo->start_time ,philo->id);
	return (0);
}

int philo_eats(t_philo *philo)
{
	size_t time;

	time = get_current_time_in_ms();
	if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
		return (0);
	if(philo->superv->dead_flag == 1)
		return (1);
	if(!are_forks_locked(philo))
	{
		pthread_mutex_lock(&philo->r_fork);
		printf("%ld %d picked a fork\n", time - philo->start_time ,philo->id);
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d picked a fork\n", time - philo->start_time ,philo->id);
		printf("%ld %d is eating\n", time - philo->start_time ,philo->id);
		philo->last_meal = time - philo->start_time;
		philo->meals_eaten++;
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
	return (0);
}

void *are_forks_locked(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	if (pthread_mutex_trylock(&ph->r_fork) == 0) 
		pthread_mutex_unlock(&ph->r_fork);
	else 
		return(NULL);
	if (pthread_mutex_trylock(ph->l_fork) == 0) 
		pthread_mutex_unlock(ph->l_fork);
	else 
		return (NULL);
	exit(0);
}
