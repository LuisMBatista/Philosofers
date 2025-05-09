/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:18:08 by lumiguel          #+#    #+#             */
/*   Updated: 2025/02/17 17:34:30 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *text)
{
	long int	time;

	pthread_mutex_lock(&(philo->superv->dead_mutex));
	pthread_mutex_lock(&(philo->superv->print));
	time = timestamps() - philo->start_time;
	if (philo->superv->dead_flag == 0)
		printf("%ld %d %s\n", time, philo->id, text);
	if (ft_strncmp(text, "died", 4) == 0)
		philo->superv->dead_flag = 1;
	pthread_mutex_unlock(&(philo->superv->print));
	pthread_mutex_unlock(&(philo->superv->dead_mutex));
}

void	betterusleep(int time)
{
	long int	now;

	now = timestamps();
	while (timestamps() - now < time)
		usleep(100);
}

long int	timestamps(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_even(int i)
{
	if (i % 2 == 0)
		return (1);
	else
		return (0);
}
