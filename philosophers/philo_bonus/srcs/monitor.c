/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:49:07 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/24 07:17:51 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	kill_all_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i <= info->num_of_philosophers)
	{
		kill(info->philo_pid[i], SIGINT);
		waitpid(info->philo_pid[i], NULL, 0);
		i++;
	}
}

void	make_monitor(t_philo *philos, t_info *info)
{
	pthread_t	monitor_tid;

	philos->info = info;
	if (pthread_create(&monitor_tid, NULL, monitor, philos) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
	if (pthread_detach(monitor_tid) != 0)
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
		sem_wait(info->sem_lock);
		if (philos[i].meals_eaten < info->meals_to_eat)
		{
			sem_post(info->sem_lock);
			return (false);
		}
		sem_post(info->sem_lock);
		i++;
	}
	sem_wait(info->sem_print);
	return (true);
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

void	*monitor(void *philo)
{
	t_philo	*philos;
	t_info	*info;
	int		starving_philosopher;

	philos = (t_philo *)philo;
	info = (t_info *)philos->info;
	usleep(info->time_to_die / 2);
	while (!eating_requirement_met(philos, info))
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
	kill_all_philos(info);
	sem_post(info->sem_print);
	return (NULL);
}
