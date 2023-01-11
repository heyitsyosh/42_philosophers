/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:13:49 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/12 01:26:08 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

bool	should_end_thread(t_info *info)
{
	pthread_mutex_lock(&info->exit_status);
	if (info->should_exit)
	{
		pthread_mutex_unlock(&info->exit_status);
		return (true);
	}
	pthread_mutex_unlock(&info->exit_status);
	return (false);
}

void	make_monitor(t_philo *philos, t_info *info)
{
	if (pthread_create(&info->monitor_tid, NULL, life, philos) != 0)
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
		if (philos[i].meals_eaten < info->meals_to_eat)
			return (false);
		i++;
	}
	return (true);
}

static int	find_starving(long now, t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	printf("info->num_of_philo: %d\n", info->num_of_philosophers);
	while (i < info->num_of_philosophers)
	{
		printf("%ld - %ld > %ld\n", now, philos[i].time_of_last_meal,  info->time_to_die);
		if (now - philos[i].time_of_last_meal > info->time_to_die)
			return (i);
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
	printf("aaa\n");
	while (!eating_requirement_met(philos, info))
	{
		starving_philosopher = find_starving(time_in_ms(), philos, info);
		if (starving_philosopher != -1)
		{
			print_action(timestamp(&philos[starving_philosopher]), \
				&philos[starving_philosopher], info, DIE_MSG);
			break ;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&info->exit_status);
	info->should_exit = true;
	pthread_mutex_unlock(&info->exit_status);
	return (NULL);
}
