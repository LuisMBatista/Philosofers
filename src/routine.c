/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:54:47 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/15 16:21:03 by lumiguel         ###   ########.fr       */
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
		puts("joined");
		i++;
	}
}

void *philo_routine(void *philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		usleep(100);
while (1)
{
    // Lock a mutex that ensures atomic checking and locking of both forks
    pthread_mutex_lock(&ph->mutex_check_forks);

    // Check if both forks are available
    if (pthread_mutex_trylock(&ph->r_fork) == 0) {
        if (pthread_mutex_trylock(ph->l_fork) == 0) {
            // Successfully locked both forks
            pthread_mutex_unlock(&ph->mutex_check_forks); // Release check lock after acquiring forks

            printf("%ld %d has taken a fork\n", get_current_time_in_ms() - ph->start_time, ph->id);
            printf("%ld %d has taken a fork\n", get_current_time_in_ms() - ph->start_time, ph->id);
            philo_eats(ph);

            pthread_mutex_unlock(ph->l_fork);
            pthread_mutex_unlock(&ph->r_fork);
        } else {
            // Could not lock the left fork, release the right fork
            pthread_mutex_unlock(&ph->r_fork);
            pthread_mutex_unlock(&ph->mutex_check_forks); // Release check lock

            // Optionally, have a small delay or yield to avoid busy-waiting
            usleep(100);
        }
    } else {
        // Release the check lock if the right fork could not be locked
        pthread_mutex_unlock(&ph->mutex_check_forks);
    }

    philo_sleeps(ph);
}
	return (NULL);
}
