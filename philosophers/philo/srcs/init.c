/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:15:45 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/31 14:53:41 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>
#include <stdlib.h>

//left and right fork of last philosopher is flipped for mutex hierarchy
static void	init_philo(t_philo *philo, t_info *info, int i)
{
	philo->info = info;
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = i + 1;
	philo->meals_eaten = 0;
	if (i + 1 == info->num_of_philosophers)
	{
		philo->right_fork = i;
		philo->left_fork = 0;
	}
}

int	make_philos(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		init_philo(&philos[i], info, i);
		if (pthread_create(&philos[i].tid, NULL, life, &philos[i]) != 0)
		{
			ft_putstr_fd("failed to create thread\n", STDERR_FILENO);
			return (i);
		}
		i++;
	}
	return (i);
}

void	join_philo_threads(t_philo *philos, t_info *info)
{
	while (info->threads_created-- > 0)
	{
		if (pthread_join(philos[info->threads_created].tid, NULL) != 0)
			ft_putstr_fd("failed to join thread\n", STDERR_FILENO);
	}
}

bool	make_mutexes(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->print, NULL);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philo_mtx[i], NULL);
		i++;
	}
	return (true);
}

bool	malloc_forks_and_philos(t_philo **philos, t_info *i)
{
	*philos = malloc(sizeof(t_philo) * i->num_of_philosophers);
	i->forks = malloc(sizeof(pthread_mutex_t) * i->num_of_philosophers);
	i->philo_mtx = malloc(sizeof(pthread_mutex_t) * i->num_of_philosophers);
	if (!philos || !i->forks || !i->philo_mtx)
	{
		free(*philos);
		free(i->forks);
		free(i->philo_mtx);
		return (false);
	}
	return (true);
}
