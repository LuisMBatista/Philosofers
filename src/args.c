/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:52:02 by lumiguel          #+#    #+#             */
/*   Updated: 2025/05/10 17:30:38 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	if (check_av(av) == 1)
		return (1);
	if (one_philo(av) == 1)
		return (1);
	return (0);
}

int	check_av(char **av)
{
	int		i;
	long	value;

	i = 1;
	while (av[i] != NULL)
	{
		if (ll_check(av[i]) == 1)
			return (1);
		value = ft_atol(av[i]);
		if ((value < 1 || value > INT_MAX) && i != 1)
		{
			printf("Error: Arguments must be between 1 and INT_MAX\n");
			return (1);
		}
		if ((i == 1) && (value > 250 || value < 1))
		{
			printf("Error: Number of philosofers between 1 and 250\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ll_check(char *av)
{
	int		i;

	i = 0;
	while (av[i] != '\0')
	{
		if ((av[i] < '0' || av[i] > '9'))
		{
			if (!(i == 0 && av[0] == '-'))
			{
				printf("Error: Arguments must be integers\n");
				return (1);
			}
		}
		i++;
	}
	if (ft_strlen(av) > 10)
	{
		printf("Error: Arguments must be between 1 and INT_MAX\n");
		return (1);
	}
	return (0);
}

int	one_philo(char **av)
{
	if (ft_atol(av[1]) == 1)
	{
		betterusleep(ft_atol(av[2]));
		printf("%ld 1 died\n", ft_atol(av[2]));
		return (1);
	}
	return (0);
}
