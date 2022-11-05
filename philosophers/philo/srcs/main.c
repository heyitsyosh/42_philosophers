/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:04:13 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/05 12:34:23 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philosopher *philos, t_info *i, int j)
{
	philos->i = i;
	philos->id = j + 1;
	philos->left_fork = j;
	philos->right_fork = j + 1;
	if (j == i->num_of_philosophers - 1)
		philos->right_fork = 0;
	philos->meals_eaten = 0;
}

long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

static void	make_philos_and_forks(t_philosopher *philos, t_info *i)
{
	int				j;

	j = 0;
	i->start_time = time_in_ms();
	while (j < i->num_of_philosophers)
	{
		init_philo(philos, i, j);
		if (pthread_create(&philos[j].tid, NULL, life, &philos[j]) != 0)
		{
			printf("failed to create thread\n");
			return ;
		}
		pthread_join(philos[j].tid, NULL);
	}
}

static void	destroy_forks(t_philosopher *philos, t_info *i)
{
	
}

int	main(int argc, char **argv)
{
	t_info			i;
	t_philosopher	*philos;

	if (!convert_input(argc, argv, &i))
	{
		printf("invalid arguments\n");
		return (0);
	}
	philos = malloc(sizeof(t_philosopher) * i.num_of_philosophers);
	if (!philos)
	{
		printf("malloc failed\n");
		return (0);
	}
	make_philos_and_forks(philos, &i);
	destroy_forks(philos, &i);
}
