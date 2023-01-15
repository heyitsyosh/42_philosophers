/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:04:13 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/15 18:12:27 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>

static void	deinitialize(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philosophers)
		pthread_mutex_destroy(&info->philo_mtx[i++]);
	i = 0;
	while (i < info->num_of_philosophers)
		pthread_mutex_destroy(&info->forks[i++]);
	if (info->num_of_philosophers < 0)
		pthread_mutex_destroy(&info->print);
	free(info->philo_mtx);
	free(info->forks);
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
	if (!malloc_forks_and_philos(&philos, &info))
		return (1);
	if (!make_mutexes(&info))
		return (1);
	info.threads_created = make_philos(philos, &info);
	make_and_detach_monitor(philos, &info);
	join_philo_threads(philos, &info);
	deinitialize(philos, &info);
}
