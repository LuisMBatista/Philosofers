/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:40:58 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/15 15:55:36 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_sleeps(t_philo *philo)
{
	size_t time;

	time = get_current_time_in_ms();
	if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
		return (0);
	printf("%ld %d is sleeping\n", time - philo->start_time ,philo->id);
		usleep(philo->time_to_sleep * 1000);
	printf("%ld %d is thinking\n", time - philo->start_time ,philo->id);
	if (get_current_time_in_ms() - (philo->start_time + philo->last_meal) > philo->time_to_die)
	{
		printf("%ld %d died\n", time - philo->start_time ,philo->id);
		*philo->dead = 1;
		return (1);
	}
	return (0);
}

int philo_eats(t_philo *philo)
{
	size_t time;

	time = get_current_time_in_ms();
	printf("%ld %d is eating\n", time - philo->start_time ,philo->id);
	philo->last_meal = time - philo->start_time;
	philo->meals_eaten++;
	usleep(philo->time_to_eat * 1000);
	return (0);
}
