/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:15:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/11 21:15:07 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

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
	bool			should_exit;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor_tid;
	pthread_mutex_t	print;
	pthread_mutex_t	exit_status;
	pthread_t		monitor_tid;
	int				threads_created;
	bool			overflow;
}	t_info;

typedef struct s_philo{
	t_info		*info;
	pthread_t	tid;
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long		start_time;
	long		time_of_last_meal;
}	t_philo;

bool	convert_input(int argc, char **argv, t_info *p);

int		philo_atoi(const char *str, t_info *p);
int		ft_strcmp(const char *s1, const char *s2);

long	time_in_ms(void);
long	timestamp(t_philo *philo);

void	precise_sleep(long target_time, t_philo *p);
void	print_action(t_philo *philo, t_info *i, char *action);

bool	malloc_forks_and_philos(t_philo **philos, t_info *i);
bool	make_forks_and_mutex(t_philo *philos, t_info *i);
int		make_philos(t_philo *philos, t_info *i);
void	join_philos(t_philo *philos, t_info *i);

void	*life(void *p);

void	make_monitor(t_philo *philos, t_info *info);
void	*monitor(void *info);
bool	should_end_thread(t_info *info);

void	deinitialize(int forks_to_destroy, t_philo *philos, t_info *i);

#endif