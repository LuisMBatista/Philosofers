/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:40:58 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/14 22:04:10 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_sleeps(t_philo *philo)
{
	size_t time;

	time = get_current_time_in_ms();
	while (get_current_time_in_ms() - time < philo->time_to_sleep)
		usleep(100);
	return (0);
}

int philo_eats(t_philo *philo)
{
	size_t time;

	time = get_current_time_in_ms();
	printf("%ld philo %d is eating\n", get_current_time_in_ms() - philo->start_time ,philo->id);
	while (get_current_time_in_ms() - time < philo->time_to_eat)
		usleep(100);
	philo->meals_eaten++;
	return (0);
}
