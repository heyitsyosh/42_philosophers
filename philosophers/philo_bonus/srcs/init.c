/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:15:45 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/27 01:44:55 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void	make_semaphores(t_info *info)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_LOCK);
	sem_unlink(SEM_MINIMUM_REQUIREMENT);
	info->ate_minimum_req = sem_open(SEM_MINIMUM_REQUIREMENT, O_CREAT | O_EXCL,
			S_IWUSR, info->num_of_philosophers);
	info->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL,
			S_IWUSR, info->num_of_philosophers);
	info->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, S_IWUSR, 1);
	info->sem_lock = sem_open(SEM_LOCK, O_CREAT | O_EXCL, S_IWUSR, 1);
	if (info->sem_print == SEM_FAILED || info->sem_lock == SEM_FAILED
		|| info->forks == SEM_FAILED)
		exit(EXIT_FAILURE);
}

static t_philo	*init_philo(int i, t_philo *philo)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	return (philo);
}

void	make_philos(t_philo *philos, t_info *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	info->philo_pid = malloc(sizeof(pid_t) * info->num_of_philosophers);
	if (!info->philo_pid)
		exit (EXIT_FAILURE);
	while (i < info->num_of_philosophers)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			life(init_philo(i, &philos[i]), info);
			make_starvation_monitor(&philos[i]);
		}
		else
			info->philo_pid[i] = pid;
		i++;
	}
}
