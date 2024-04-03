/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:14:48 by myoshika          #+#    #+#             */
/*   Updated: 2024/04/03 21:26:18 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdlib.h> //malloc, free
#include <unistd.h> //STDERR_FILENO

void	deinitialize(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philosophers)
	{
		sem_close(info->sem_lock[i]);
		i++;
	}
	sem_close(info->sem_print);
	sem_close(info->forks);
	sem_close(info->ate_minimum_req);
	free(info->philo_pid);
	free(info->sem_lock);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philos;

	if (!convert_input(argc, argv, &info))
	{
		ft_putstr_fd("invalid arguments\n", STDERR_FILENO);
		return (0);
	}
	philos = malloc(sizeof(t_philo) * info.num_of_philosophers);
	if (!philos)
		print_error_and_exit("malloc failure\n");
	make_semaphores(&info);
	make_philos(philos, &info);
	make_times_eaten_monitor(&info);
	make_stop_simulation_monitor(&info);
	wait_for_monitors_to_detect(&info);
	deinitialize(philos, &info);
	return (0);
}
