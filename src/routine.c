/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:47 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/18 18:14:46 by lumiguel         ###   ########.fr       */
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
		//pthread_create(&superv->mutex_check_forks, NULL, &are_forks_locked,&superv->philos[i]); // queria mudar para ser so 1
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
			break;
		if (philo_eats(ph))
			philo_sleeps(ph);
		if (ph->num_times_to_eat != -1 && ph->meals_eaten >= ph->num_times_to_eat)
			break;
		if (timestamps() - (ph->start_time + ph->last_meal) > ph->time_to_die)
		{
			print(philo,"died");
			*ph->dead = 1;
			break;
		}
	}
	return(NULL);
}
int philo_sleeps(t_philo *philo)
{
	long int time;

	time = timestamps();
	if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
		return (0);
	print(philo,"is sleeping");
	while (timestamps() - time < philo->time_to_sleep)
	{
		if (timestamps() - (philo->start_time + philo->last_meal) > philo->time_to_die)
		{
			print(philo,"died");
			*philo->dead = 1;
			puts("bom dia");
			break;
		}
		betterusleep(philo->time_to_sleep /100);
	}
	if(timestamps() - time > philo->time_to_sleep)
		print(philo,"is thinking");
	return (0);
}

int philo_eats(t_philo *philo)
{
	long time;

	if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
		return (0);
	if(philo->superv->dead_flag == 1)
		return (0);
	if(philo->num_of_philos == 1)
		return(0);
	if (philo->id % 2 == 0)
    usleep(100);
	pthread_mutex_lock(&philo->r_fork);
	print(philo,"has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print(philo,"has taken a fork");
	print(philo,"is eating");
	time = timestamps();
	philo->last_meal = time - philo->start_time;
	philo->meals_eaten++;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	return(1);
}

