/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:49:07 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/27 04:51:00 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pthread_t	make_times_eaten_monitor(t_info *info)
{
	pthread_t	monitor_tid;

	if (pthread_create(&monitor_tid, NULL, times_eaten_monitor, info) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
}

void	*times_eaten_monitor(void *ptr_to_info)
{
	t_info	*info;
	int		i;

	info = (t_info *)ptr_to_info;
	if (info->meals_to_eat == -1)
		return (NULL);
	usleep(info->time_to_eat / 2);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		sem_wait(info->ate_minimum_req);
		i++;
	}
	sem_wait(info->sem_print);
	if (!info->philos_killed)
		kill_all_philos(info);
	sem_post(info->sem_print);
	return (NULL);
}

void	make_starvation_monitor(t_philo *philos, t_info *info)
{
	pthread_t	monitor_tid;

	philos->info = info;
	if (pthread_create(&monitor_tid, NULL, starvation_monitor, philos) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
}

static int	find_starving(long now, t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		sem_wait(info->sem_lock);
		if (now - philos[i].time_of_last_meal > info->time_to_die)
		{
			sem_post(info->sem_lock);
			return (i);
		}
		sem_post(info->sem_lock);
		i++;
	}
	return (-1);
}

void	*starvation_monitor(void *philo)
{
	t_philo	*philos;
	t_info	*info;
	int		starving_philosopher;

	philos = (t_philo *)philo;
	info = (t_info *)philos->info;
	usleep(info->time_to_die / 2);
	while (simulation_active(info))
	{
		starving_philosopher = find_starving(time_in_ms(), philos, info);
		if (starving_philosopher != -1)
		{
			sem_wait(info->sem_print);
			printf("%ld %d %s\n", timestamp_in_ms(&philos[starving_philosopher]),
				starving_philosopher + 1, DIE_MSG);
			break ;
		}
		usleep(1000);
	}
	if (!info->philos_killed)
		kill_all_philos(info);
	sem_post(info->sem_print);
	return (NULL);
}
