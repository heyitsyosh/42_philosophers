/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:43:46 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/27 04:51:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	wait_for_monitors_to_detect(t_info *info)
{
	int	i;

	i = 0;
	while (i <= info->num_of_philosophers)
	{
		if (pthread_join(info->starvation_monitors[i], NULL) != 0)
			printf("failed to join thread\n");
		i++;
	}
	kill(info->times_eaten_monitor_tid, SIGINT);
	waitpid(info->times_eaten_monitor_tid, NULL, 0);
}

void	kill_all_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i <= info->num_of_philosophers)
	{
		kill(info->philo_pid[i], SIGINT);
		waitpid(info->philo_pid[i], NULL, 0);
		i++;
	}
	info->philos_killed = true;
}
