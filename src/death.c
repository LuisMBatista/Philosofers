/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:24:01 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/24 22:15:03 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death_condition(t_philo *philo)
{
	if (philo->dead == 1)
	{
		pthread_mutex_lock(&philo->superv->dead_mutex);
		philo->superv->dead_flag = 1;
		pthread_mutex_unlock(&philo->superv->dead_mutex);
	}
 	else
		pthread_mutex_unlock(&philo->superv->dead_mutex);
	return 0;
}

void *check_death(void *superv)
{
    t_superv *death = (t_superv *)superv;
    int i;
    while (1)
    {
        i = 0;
        while (i < death->philos[0].num_of_philos && death->dead_flag == 0)
        {
        	check_death_condition(&death->philos[i]);
			i++;
		}
		betterusleep(100);
		pthread_mutex_lock(&death->dead_mutex);
		if(death->dead_flag == 1)
		{
			pthread_mutex_unlock(&death->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&death->dead_mutex);
	}
    return (NULL);
} 
