/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:47 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/14 16:56:45 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_superv *superv)
{
	int i;

	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		pthread_create(&superv->philos[i].thread, NULL, &philo_routine, &superv->philos[i]);
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
		pthread_mutex_lock(ph->r_fork);
		pthread_mutex_lock(ph->l_fork);
		philo_eats(ph);
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
		philo_sleeps(ph);
	}
	return (NULL);
}
