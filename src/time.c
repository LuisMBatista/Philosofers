/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:18:08 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/19 17:51:14 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *text)
{
	long int	time;

	pthread_mutex_lock(&(philo->superv->print));
	time = timestamps() - philo->start_time;
	if (philo->superv->dead_flag == 0)
		printf("%ld %d %s\n", time, philo->id, text);
	if (ft_strncmp(text, "died\n", 6) == 0)
		philo->superv->dead_flag = 1;
	pthread_mutex_unlock(&(philo->superv->print));
}

void	betterusleep(int time)
{
	long int	now;

	now = timestamps();
	while (timestamps() - now < time)
		usleep(350);
}

long int	timestamps(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

