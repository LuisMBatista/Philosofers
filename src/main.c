/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:05:02 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/14 22:05:56 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_superv	superv;
	
	check_args(ac, av);
	superv.dead_flag = 0;
	superv.philos = malloc(sizeof(t_philo) * ft_atol(av[1]));
	if (!superv.philos)
	{
		printf("Error: Inicial malloc failed");
		exit(1);
	}
	init_philos(&superv, av, ac);
	fork_pointing(&superv);
	routine(&superv);
	return (0);
}

