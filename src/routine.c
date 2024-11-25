/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:47 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/25 17:23:32 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *philo) 
{
	t_philo *ph = (t_philo *)philo;
	
	while (1) 
	{
		pthread_mutex_lock(&ph->superv->dead_mutex);
		if(ph->superv->finish == 1 || ph->dead == 1)
		{
			puts("checkers");
			pthread_mutex_unlock(&ph->superv->dead_mutex);
			break;
		}
		if (timestamps() - ph->last_meal > ph->time_to_die)
		{
			puts("checkers1");
			pthread_mutex_unlock(&ph->superv->dead_mutex);
			print(philo,"died");
			break;
		}
		pthread_mutex_unlock(&ph->superv->dead_mutex);
		if (philo_eats(ph))
		{
			if (philo_sleeps(ph) == 0)
				break;	
		}
		if (ph->dead == 1)
			break;
	}
	return NULL;
}

int philo_eats(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(&philo->r_fork);
    }
    else
    {
        pthread_mutex_lock(&philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
    }
	pthread_mutex_lock(&philo->superv->dead_mutex);
	if(philo->superv->finish == 1)
	{
		pthread_mutex_unlock(&philo->superv->dead_mutex);
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return(0);
	}
	pthread_mutex_unlock(&philo->superv->dead_mutex);
	if (timestamps() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print(philo,"died");
		philo->dead = 1;
		return(0);
	}
	print(philo,"has taken a fork");
	print(philo,"has taken a fork");
	print(philo,"is eating");
	philo->last_meal =timestamps();
	philo->meals_eaten++;
	betterusleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	
	return(1);
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
		if (timestamps() - philo->last_meal > philo->time_to_die)
		{
			print(philo,"died");
			philo->dead = 1;
			return(0);
		}
		betterusleep(philo->time_to_sleep /20);
	}
	pthread_mutex_lock(&philo->superv->dead_mutex);
	if (philo->superv->finish == 1)
	{
		pthread_mutex_unlock(&philo->superv->dead_mutex);
		return(0);
	}
	pthread_mutex_unlock(&philo->superv->dead_mutex);
	print(philo,"is thinking");
	return (1);
}

