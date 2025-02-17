/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:05:02 by lumiguel          #+#    #+#             */
/*   Updated: 2025/02/17 17:27:54 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_superv	superv;

	memset(&superv, 0, sizeof(t_superv));
	if (check_args(ac, av) == 1)
		return (1);
	superv.dead_flag = 0;
	superv.philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!superv.philos)
	{
		printf("Error: Inicial malloc failed");
		return (1);
	}
	init_philos(&superv, av, ac);
	thread_creation(&superv);
	free(superv.philos);
	return (0);
}
