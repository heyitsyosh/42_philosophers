/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:19 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/07 20:33:30 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <string.h> //memset
# include <stdlib.h> //malloc, free
# include <unistd.h> //read, write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

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
	long			time_to_think;
	int				meals_to_eat;
	long			start_time;
	bool			should_exit;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	bool			overflow;
}	t_info;

typedef struct s_philo{
	t_info		*i;
	pthread_t	tid;
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long		time_of_last_meal;
}	t_philo;

bool	convert_input(int argc, char **argv, t_info *p);

int		philo_atoi(const char *str, t_info *p);
int		ft_strcmp(const char *s1, const char *s2);

long	time_in_ms(void);
long	timestamp(t_info *i);

void	print_action(t_philo *philo, t_info *i, char *action);

t_philo	*malloc_forks_and_philos(t_info *i);
bool	make_forks_and_mutex(t_philo *philos, t_info *i);
void	make_philos(t_philo *philos, t_info *i);

void	*life(void *p);

void	deinitialize(int forks_to_destroy, t_philo *philos, t_info *i);

#endif