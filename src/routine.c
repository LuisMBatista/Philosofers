/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:47 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/21 21:22:54 by lumiguel         ###   ########.fr       */
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
		i++;
	}
	pthread_create(&superv->check_death,NULL, &check_death,&superv);
	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		pthread_join(superv->philos[i].thread, NULL);
		i++;
	}
}

void *philo_routine(void *philo) 
{
	t_philo *ph = (t_philo *)philo;
	
	while (1) 
	{
		if (ph->num_times_to_eat != -1 && ph->meals_eaten >= ph->num_times_to_eat)
			break;
		if (timestamps() - ph->last_meal > ph->time_to_die)
		{
			ph->dead = 1;
			print(philo,"died");
			break;
		}
		if (philo_eats(ph))
			philo_sleeps(ph);
		if (ph->dead == 1)
			break;
	}
	return NULL;
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
			philo->dead = 1;
			print(philo,"died");
			return(1);
		}
		betterusleep(philo->time_to_sleep /20);
	}
	if (timestamps() - philo->last_meal > philo->time_to_die)
	{
		philo->dead = 1;
		print(philo,"died");
		return(1);
	}
	print(philo,"is thinking");
	return (0);
}

int philo_eats(t_philo *philo)
{
	if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
		return (0);
	if (philo->dead == 1)
		return(0);
	if(philo->num_of_philos == 1)
		return(0);
	if (timestamps() - philo->last_meal > philo->time_to_die)
	{
		philo->dead = 1;
		print(philo,"died");
		return(1);
	}
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

int check_death_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->superv->dead_mutex);
	if(philo->superv->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->superv->dead_mutex);
		return(0); //another is already dead TIRAR ISTO NA ROTINA DO MONITOR
	}
			
	if ((timestamps() - philo->last_meal) > philo->time_to_die)
	{
		philo->superv->dead_flag = 1;
		print(philo, "died");
		pthread_mutex_unlock(&philo->superv->dead_mutex);
		return 1; // Indicates death
	}
	pthread_mutex_unlock(&philo->superv->dead_mutex);
	return 0; // Alive
}

 void *check_death(void *superv)
{
    t_superv *death = (t_superv *)superv;
    int i;

    if (!death || !death->philos) // Null check for `death` and `philos`.
    {
        fprintf(stderr, "Invalid supervisor or philos pointer\n");
        return (NULL);
    }
    while (1)
    {
        i = 0;
        while (i < death->philos->num_of_philos)
        {
            check_death_condition(&death->philos[i]);
			i++;
		}
		if(death->dead_flag == 1)
			break;
	}
    return (NULL);
} 
