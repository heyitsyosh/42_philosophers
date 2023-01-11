/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:15:45 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/11 21:26:04 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>

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
			printf("failed to create thread\n");
			return (i);
		}
		i++;
	}
	return (i);
}

void	join_philos(t_philo *philos, t_info *info)
{
	while (info->threads_created-- > 0)
	{
		if (pthread_join(philos[info->threads_created].tid, NULL) != 0)
			printf("failed to join thread\n");
	}
}

bool	make_forks_and_mutex(t_philo *philos, t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->print, NULL))
	{
		deinitialize(-1, philos, info);
		return (false);
	}
	if (pthread_mutex_init(&info->exit_status, NULL))
	{
		deinitialize(-2, philos, info);
		return (false);
	}
	i = 0;
	while (i < info->num_of_philosophers)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			deinitialize(i, philos, info);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	malloc_forks_and_philos(t_philo **philos, t_info *info)
{
	*philos = malloc(sizeof(t_philo) * info->num_of_philosophers);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philosophers);
	if (!philos || !info->forks)
	{
		free(*philos);
		free(info->forks);
		return (false);
	}
	return (true);
}
