/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:21 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/22 07:48:58 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdbool.h>

# define MAX_PHILOS 200

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
	sem_t			*sem_print;
	sem_t			*sem_lock;
	sem_t			*forks;
	//bool			should_exit;
	bool			overflow;
}	t_info;

typedef struct s_philo{
	int			id;
	int			meals_eaten;
}	t_philo;

bool	convert_input(int argc, char **argv, t_info *p);
int		philo_atoi(const char *str, t_info *p);

void	make_semaphores(t_info *info);
void	make_philos(t_philo *philo, t_info *info);

void	life(t_philo *p, t_info *i);

void	sleep_till(long target_time_ms, t_philo *philo);
bool	print_action(long time, t_philo *philo, t_info *i, char *action);

#endif