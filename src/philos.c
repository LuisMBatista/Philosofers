/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:29:50 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/14 22:05:46 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philos(t_superv *superv, char **av, int ac)
{
	int i;
	
	i = 0;
	while (i < ft_atol(av[1]))
	{
		superv->philos[i].id = i;
		superv->philos[i].eating = 0;
		superv->philos[i].meals_eaten = 0;
		superv->philos[i].num_of_philos = ft_atol(av[1]);
		superv->philos[i].dead = &superv->dead_flag;
		superv->philos[i].last_meal = 0;
		superv->philos[i].time_to_die = ft_atol(av[2]);
		superv->philos[i].time_to_eat = ft_atol(av[3]);
		superv->philos[i].time_to_sleep = ft_atol(av[4]);
		superv->philos[i].start_time = get_current_time_in_ms();
		superv->philos[i].r_fork = malloc(sizeof(pthread_mutex_t));
		superv->philos[i].l_fork = malloc(sizeof(pthread_mutex_t));
		check_eating_times(superv, av, ac);
		if (!superv->philos[i].r_fork || !superv->philos[i].l_fork)
			exit(1);
		pthread_mutex_init(superv->philos[i].r_fork, NULL);
		pthread_mutex_init(superv->philos[i].l_fork, NULL);
		i++;
	}
	return (0);
}

void fork_pointing(t_superv *superv)
{
	int i;
	
	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		if (i == 0)
		{
			superv->philos[i].r_fork = superv->philos[superv->philos[0].num_of_philos - 1].l_fork;
			superv->philos[i].l_fork = superv->philos[i + 1].r_fork;
		}
		else if (i == superv->philos[0].num_of_philos - 1)
		{
			superv->philos[i].r_fork = superv->philos[i - 1].l_fork;
			superv->philos[i].l_fork = superv->philos[0].r_fork;
		}
		else
		{
			superv->philos[i].r_fork = superv->philos[i - 1].l_fork;
			superv->philos[i].l_fork = superv->philos[i + 1].r_fork;
		}
		i++;
	}
}

void check_eating_times(t_superv *superv, char **av, int ac)
{
	int i;

	i = 0;
	if (ac == 6)
		superv->philos[i].num_times_to_eat = ft_atol(av[5]);
	else
		superv->philos[i].num_times_to_eat = -1;
}
