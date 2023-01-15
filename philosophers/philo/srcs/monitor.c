/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:13:49 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/15 14:45:35 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

void	make_and_detach_monitor(t_philo *philos, t_info *info)
{
	if (pthread_create(&info->monitor_tid, NULL, monitor, philos) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
	if (pthread_detach(info->monitor_tid) != 0)
		printf("failed to detach thread\n");
}

static bool	eating_requirement_met(t_philo *philos, t_info *info)
{
	int	i;

	if (info->meals_to_eat == -1)
		return (false);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		pthread_mutex_lock(&info->philo_mtx[i]);
		if (philos[i].meals_eaten < info->meals_to_eat)
		{
			pthread_mutex_unlock(&info->philo_mtx[i]);
			return (false);
		}
		pthread_mutex_unlock(&info->philo_mtx[i]);
		i++;
	}
	pthread_mutex_lock(&info->print);
	return (true);
}

static int	find_starving(long now, t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		pthread_mutex_lock(&info->philo_mtx[i]);
		if (now - philos[i].time_of_last_meal > info->time_to_die)
		{
			pthread_mutex_unlock(&info->philo_mtx[i]);
			return (i);
		}
		pthread_mutex_unlock(&info->philo_mtx[i]);
		i++;
	}
	return (-1);
}

void	*monitor(void *philo)
{
	t_philo	*philos;
	t_info	*info;
	int		starving_philosopher;

	philos = (t_philo *)philo;
	info = (t_info *)philos->info;
	while (!eating_requirement_met(philos, info))
	{
		starving_philosopher = find_starving(time_in_usec(), philos, info);
		if (starving_philosopher != -1)
		{
			pthread_mutex_lock(&info->print);
			printf("%ld %d %s\n", timestamp_in_ms(&philos[starving_philosopher]),
				starving_philosopher + 1, DIE_MSG);
			break ;
		}
		usleep(1000);
	}
	info->should_exit = true;
	pthread_mutex_unlock(&info->print);
	return (NULL);
}
