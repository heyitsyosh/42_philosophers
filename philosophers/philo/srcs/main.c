/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:04:13 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/06 23:23:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deinitialize(int forks_to_destroy, t_philo *philos, t_info *i)
{
	if (forks_to_destroy != i->num_of_philosophers)
		printf("failed to initialize mutex\n");
	while (forks_to_destroy-- > 0)
		pthread_mutex_destroy(&i->forks[forks_to_destroy]);
	pthread_mutex_destroy(&i->print);
	free(i->forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	int		j;
	t_info	i;
	t_philo	*philos;

	if (!convert_input(argc, argv, &i))
	{
		printf("invalid arguments\n");
		return (0);
	}
	philos = malloc_forks_and_philos(&i);
	if (!philos)
	{
		printf("malloc failure\n");
		return (0);
	}
	if (!make_forks_and_mutex(philos, &i))
		return (0);
	make_philos(philos, &i);
	deinitialize(i.num_of_philosophers, philos, &i);
}
