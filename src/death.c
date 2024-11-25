/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:24:01 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/25 18:40:42 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_condition(t_superv *superv)
{
	pthread_mutex_lock(&superv->dead_mutex);
	if (superv->dead_flag == 1)
	{
		superv->finish = 1;
		pthread_mutex_unlock(&superv->dead_mutex);
	}
	else
		pthread_mutex_unlock(&superv->dead_mutex);
	return (0);
}

void	*check_death(void *superv)
{
	t_superv	*death;

	death = (t_superv *)superv;
	while (1)
	{
		if (death->finish == 0)
		{
			finish_condition(death);
			betterusleep(100);
		}
		pthread_mutex_lock(&death->dead_mutex);
		if (death->finish == 1 || death->everyone_ate == 1)
		{
			pthread_mutex_unlock(&death->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&death->dead_mutex);
	}
	return (NULL);
}
