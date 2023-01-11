/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:14:48 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/10 07:31:28 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	philos = make_forks_and_philos(&i);
	if (!philos)
	{
		printf("malloc failure\n");
		return (1);
	}
	if (!make_philos(philos, &i))
		return (1);
	deinitialize(i.num_of_philosophers, philos, &i);
}
