/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:32:06 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/09 14:56:56 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_range(int argc, t_info *i)
{
	if (i->overflow)
		return (false);
	if (i->num_of_philosophers < 0 || i->time_to_die <= 0 || i->time_to_eat <= 0
		|| i->time_to_sleep <= 0)
		return (false);
	if (argc == 6 && i->meals_to_eat < 0)
		return (false);
	return (true);
}

static bool	str_is_num(char *str)
{
	if (!*str)
		return (false);
	if (*str == '+')
		str++;
	while (*str)
	{
		if ('0' > *str || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static bool	check_args(int argc, char **argv)
{
	if (argc < 5 && 6 < argc)
		return (false);
	if (!str_is_num(argv[1]) || !str_is_num(argv[2])
		|| !str_is_num(argv[3]) || !str_is_num(argv[4]))
		return (false);
	if (argc == 6)
		if (!str_is_num(argv[5]))
			return (false);
	return (true);
}

bool	convert_input(int argc, char **argv, t_info *i)
{
	if (!check_args(argc, argv))
		return (false);
	i->overflow = false;
	i->should_exit = false;
	i->num_of_philosophers = philo_atoi(argv[1], i);
	i->time_to_die = philo_atoi(argv[2], i);
	i->time_to_eat = philo_atoi(argv[3], i);
	i->time_to_sleep = philo_atoi(argv[4], i);
	if (argc == 6)
		i->meals_to_eat = philo_atoi(argv[5], i);
	if (!check_range(argc, i))
		return (false);
	if (argc != 6)
		i->meals_to_eat = -1;
	return (true);
}
