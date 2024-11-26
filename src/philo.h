/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:06:24 by lumiguel          #+#    #+#             */
/*   Updated: 2024/11/26 16:12:12 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	int				dead;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	pthread_t		thread;
	pthread_mutex_t	single_dead_mutex;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	struct s_superv	*superv;
}					t_philo;

typedef struct s_superv
{
	int				dead_flag;
	int				finish;
	int				everyone_finished;
	t_philo			*philos;
	pthread_t		check_death;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
}					t_superv;

int			finish_condition(t_superv *philo);
int			check_av(char **av);
int			check_args(int ac, char **av);
int			philo_eats(t_philo *philo);
int			ll_check(char *av);
int			init_philos(t_superv *superv, char **av, int ac);
int			philo_sleeps(t_philo *philo);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			one_philo(char **av);
int			check_time(t_philo *philo);
long		ft_atol(const char *str);
long int	timestamps(void);
size_t		ft_strlen(const char *s);
size_t		get_current_time_in_ms(void);
void		check_eating_times(t_superv *superv, char **av, int ac, int i);
void		*philo_routine(void *philo);
void		thread_creation(t_superv *superv);
void		forks(t_superv *superv, int i);
void		print(t_philo *philo, char *text);
void		betterusleep(int time);
void		*check_death(void *superv);
void		fork_locking(t_philo *philo);

#endif
