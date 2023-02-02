/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:15:45 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/03 04:10:21 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static void	make_semaphore_locks(t_info *info)
{
	int		i;
	char	*id;

	i = 0;
	info->sem_lock = malloc(sizeof(sem_t *) * info->num_of_philosophers);
	while (i < info->num_of_philosophers)
	{
		id = ft_itoa(i);
		if (!id)
			print_error_and_exit("malloc failure\n");
		sem_unlink(id);
		info->sem_lock[i] = sem_open(id, O_CREAT | O_EXCL, S_IWUSR, 1);
		if (info->sem_lock[i] == SEM_FAILED)
			print_error_and_exit("semaphore creation failure\n");
		sem_unlink(id);
		free(id);
		i++;
	}
}

static void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_MIN_REQ);
}

void	make_semaphores(t_info *info)
{
	unlink_semaphores();
	info->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, S_IWUSR, 1);
	info->ate_minimum_req = sem_open(SEM_MIN_REQ, O_CREAT | O_EXCL, S_IWUSR, 0);
	info->stop_simulation = sem_open(SEM_STOP, O_CREAT | O_EXCL, S_IWUSR, 0);
	info->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, \
			S_IWUSR, info->num_of_philosophers);
	if (info->sem_print == SEM_FAILED || info->ate_minimum_req == SEM_FAILED \
		|| info->stop_simulation == SEM_FAILED || info->forks == SEM_FAILED)
		print_error_and_exit("semaphore creation failure\n");
	make_semaphore_locks(info);
	unlink_semaphores();
}

static t_philo	*init_philo(int i, t_philo *philo)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	return (philo);
}

void	make_philos(t_philo *philos, t_info *info)
{
	int		i;

	i = 0;
	info->philo_pid = malloc(sizeof(pid_t) * info->num_of_philosophers);
	if (!info->philo_pid)
		print_error_and_exit("malloc failure\n");
	while (i < info->num_of_philosophers)
	{
		info->philo_pid[i] = fork();
		if (info->philo_pid[i] == -1)
			print_error_and_exit("fork failure\n");
		else if (info->philo_pid[i] == 0)
			life(init_philo(i, &philos[i]), info);
		i++;
	}
}
