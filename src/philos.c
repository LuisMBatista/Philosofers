/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:29:50 by lumiguel          #+#    #+#             */
/*   Updated: 2025/02/17 17:33:59 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_superv *superv, char **av, int ac)
{
	int		i;

	i = -1;
	pthread_mutex_init(&superv->print, NULL);
	pthread_mutex_init(&superv->dead_mutex, NULL);
	while (++i < ft_atol(av[1]))
	{
		superv->philos[i].id = i + 1;
		superv->philos[i].eating = 0;
		superv->philos[i].meals_eaten = 0;
		superv->philos[i].num_of_philos = ft_atol(av[1]);
		superv->philos[i].dead = 0;
		superv->philos[i].last_meal = timestamps();
		superv->philos[i].start_time = timestamps();
		superv->philos[i].time_to_die = ft_atol(av[2]);
		superv->philos[i].time_to_eat = ft_atol(av[3]);
		superv->philos[i].time_to_sleep = ft_atol(av[4]);
		superv->philos[i].superv = superv;
		superv->philos[i].think_timer = 0;
		if (!is_even(ft_atol(av[1])))
			superv->philos[i].think_timer = ((superv->philos[i].time_to_eat
						*2) - superv->philos[i].time_to_sleep);
		forks(superv, av, ac, i);
	}
	return (0);
}

void	forks(t_superv *superv, char **av, int ac, int i)
{
	if (ac == 6)
		superv->philos[i].num_times_to_eat = ft_atol(av[5]);
	else
		superv->philos[i].num_times_to_eat = -1;
	pthread_mutex_init(&superv->philos[i].r_fork, NULL);
	if (i == superv->philos[0].num_of_philos - 1)
		superv->philos[i].l_fork = &superv->philos[0].r_fork;
	else
		superv->philos[i].l_fork = &superv->philos[i + 1].r_fork;
	i++;
}

void	thread_creation(t_superv *superv)
{
	int		i;

	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		pthread_create(&superv->philos[i].thread,
			NULL, &philo_routine, &superv->philos[i]);
		i++;
	}
	pthread_create(&superv->check_death, NULL, &check_death, superv);
	i = 0;
	while (i < superv->philos[0].num_of_philos)
	{
		pthread_join(superv->philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_lock(&superv->dead_mutex);
	superv->everyone_finished = 1;
	pthread_mutex_unlock(&superv->dead_mutex);
	pthread_join(superv->check_death, NULL);
}

void	think_wait(t_philo *philo)
{
	print(philo, "is thinking");
	betterusleep(philo->think_timer);
}
