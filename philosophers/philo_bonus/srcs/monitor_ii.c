/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_ii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:43:46 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/03 04:12:28 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void	make_stop_simulation_monitor(t_info *info)
{
	if (pthread_create(&info->stop_simulation_monitor_tid, NULL, \
		stop_simulation_monitor, info) != 0)
	{
		printf("failed to create thread\n");
		return ;
	}
}

void	*stop_simulation_monitor(void *ptr_to_info)
{
	t_info	*info;
	int		i;

	info = (t_info *)ptr_to_info;
	sem_wait(info->stop_simulation);
	kill_all_philos(info);
	i = 0;
	while (i < info->num_of_philosophers)
	{
		sem_post(info->ate_minimum_req);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */

void	kill_all_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i <= info->num_of_philosophers)
	{
		kill(info->philo_pid[i], SIGKILL);
		i++;
	}
}

void	wait_for_monitors_to_detect(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		if (waitpid(info->philo_pid[i], NULL, 0) == -1)
			print_error_and_exit("waitpid failure\n");
		i++;
	}
	if (pthread_join(info->times_eaten_monitor_tid, NULL))
		print_error_and_exit("failed to join thread\n");
	if (pthread_join(info->stop_simulation_monitor_tid, NULL))
		print_error_and_exit("failed to join thread\n");
}
