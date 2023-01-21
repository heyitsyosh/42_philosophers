/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:21 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/21 23:09:05 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdbool.h>

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

typedef struct s_info{
	int				num_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_to_eat;
	//bool			should_exit;
	bool			overflow;
}	t_info;

typedef struct s_philo{
	t_info		*i;
	int			id;
	size_t		meals_eaten;
}	t_philo;

bool	convert_input(int argc, char **argv, t_info *p);
int		philo_atoi(const char *str, t_info *p);

void	make_philos(t_info *info);

#endif