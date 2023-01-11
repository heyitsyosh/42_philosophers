/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:04:13 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/11 21:07:47 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <stdlib.h>

void	deinitialize(int forks_to_destroy, t_philo *philos, t_info *info)
{
	if (forks_to_destroy != info->num_of_philosophers)
		printf("failed to initialize mutex\n");
	while (forks_to_destroy-- > 0)
		pthread_mutex_destroy(&info->forks[forks_to_destroy]);
	if (forks_to_destroy < 0)
		pthread_mutex_destroy(&info->print);
	if (forks_to_destroy < -1)
		pthread_mutex_destroy(&info->exit_status);
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
	{
		printf("malloc failure\n");
		return (1);
	}
	if (!make_forks_and_mutex(philos, &info))
		return (1);
	info.threads_created = make_philos(philos, &info);
	join_philos(philos, &info);
	if (info.threads_created == info.num_of_philosophers)
		make_monitor(philos, &info);
	deinitialize(info.num_of_philosophers, philos, &info);
}
