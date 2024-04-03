/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:49:07 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/03 21:17:25 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h> //printf
#include <unistd.h> //usleep

void	make_times_eaten_monitor(t_info *info)
{
	if (pthread_create(&info->times_eaten_monitor_tid, NULL, \
		times_eaten_monitor, info) != 0)
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
	i = 0;
	while (i < info->num_of_philosophers)
	{
		sem_wait(info->ate_minimum_req);
		i++;
	}
	sem_post(info->stop_simulation);
	return (NULL);
}

void	make_starvation_monitor(t_philo *philo, t_info *info)
{
	pthread_t	monitor_tid;

	philo->info = info;
	if (pthread_create(&monitor_tid, NULL, starvation_monitor, philo) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
}

static bool	philo_is_starving(long now, t_philo *philo, t_info *info)
{
	sem_wait(info->sem_lock[philo->id - 1]);
	if (now - philo->time_of_last_meal > info->time_to_die)
	{
		sem_post(info->sem_lock[philo->id - 1]);
		return (true);
	}
	sem_post(info->sem_lock[philo->id - 1]);
	return (false);
}

void	*starvation_monitor(void *philo_ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)philo_ptr;
	info = (t_info *)philo->info;
	usleep(info->time_to_die / 2);
	while (1)
	{
		if (philo_is_starving(time_in_ms(), philo, info))
		{
			sem_wait(info->sem_print);
			printf("%ld %d %s\n",
				timestamp_in_ms(philo), philo->id + 1, DIE_MSG);
			break ;
		}
		usleep(1000);
	}
	sem_post(info->stop_simulation);
	return (NULL);
}
