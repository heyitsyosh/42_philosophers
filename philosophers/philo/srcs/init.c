/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:15:45 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/07 20:50:24 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philo(t_philo *philo, t_info *i, int j)
{
	philo->i = i;
	philo->id = j + 1;
	philo->left_fork = j;
	philo->right_fork = j + 1;
	if (j == i->num_of_philosophers - 1)
		philo->right_fork = 0;
	philo->meals_eaten = 0;
	philo->time_of_last_meal = 0;
}

void	make_philos(t_philo *philos, t_info *i)
{
	int	j;

	j = 0;
	i->start_time = time_in_ms();
	while (j < i->num_of_philosophers)
	{
		init_philo(philos, i, j);
		if (pthread_create(&philos[j].tid, NULL, life, &philos[j]) != 0)
		{
			printf("failed to create thread\n");
			return ;
		}
		pthread_join(philos[j++].tid, NULL);
	}
}

bool	make_forks_and_mutex(t_philo*philos, t_info *i)
{
	int	j;

	if (pthread_mutex_init(&i->print, NULL))
	{
		deinitialize(-1, philos, i);
		return (false);
	}
	j = 0;
	while (j < i->num_of_philosophers)
	{
		if (pthread_mutex_init(&i->forks[j], NULL))
		{
			deinitialize(j, philos, i);
			return (false);
		}
		j++;
	}
	return (true);
}

t_philo	*malloc_forks_and_philos(t_info *i)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * i->num_of_philosophers);
	if (!philos)
		return (NULL);
	i->forks = malloc(sizeof(pthread_mutex_t) * i->num_of_philosophers);
	if (!i->forks)
	{
		free(philos);
		return (NULL);
	}
	return (philos);
}
