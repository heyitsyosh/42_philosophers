/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:14:48 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/24 07:15:55 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void	deinitialize(t_philo *philos, t_info *info)
{
	sem_close(info->sem_lock);
	sem_close(info->sem_print);
	sem_close(info->forks);
	sem_unlink("sem_lock");
	sem_unlink("sem_print");
	sem_unlink("forks");
	free(philos);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (!convert_input(argc, argv, &info))
	{
		printf("invalid arguments\n");
		return (0);
	}
	philos = malloc(sizeof(t_philo) * info.num_of_philosophers);
	if (!philos)
		exit (EXIT_FAILURE);
	make_semaphores(&info);
	make_philos(philos, &info);
	make_monitor(philos, &info);
	deinitialize(philos, &info);
}
