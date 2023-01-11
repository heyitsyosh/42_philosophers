/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:13:49 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/11 21:36:46 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	info->philos = philos;
	if (pthread_create(&info->monitor_tid, NULL, life, &info) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
	if (pthread_join(info->monitor_tid, NULL) != 0)
		printf("failed to join thread\n");
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

static bool	starvation_detected()
{
	
}

void	*monitor(void *info_ptr)
{
	t_philo	*philos;
	t_info	*info;

	info = (t_info *)info_ptr;
	philos = (t_philo *)info->philos;
	while (!eating_requirement_met(philos, info))
	{
		if (starvation_detected(philos, info))
	}
	return (NULL);
}
