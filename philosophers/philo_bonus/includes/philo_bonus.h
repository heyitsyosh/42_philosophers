/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:21 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/27 04:41:42 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

# define MAX_PHILOS 200

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

# define SEM_FORKS "sem_forks"
# define SEM_PRINT "sem_print"
# define SEM_LOCK "sem_lock"
# define SEM_MINIMUM_REQUIREMENT "ate_minimum_requirement"

typedef struct s_info{
	int			num_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			meals_to_eat;
	sem_t		*sem_print;
	sem_t		*sem_lock;
	sem_t		*forks;
	sem_t		*ate_minimum_req;
	bool		should_exit;
	bool		overflow;
	bool		philos_killed;
	pid_t		*philo_pid;
	pthread_t	*starvation_monitors;
	pthread_t	times_eaten_monitor_tid;
}	t_info;

typedef struct s_philo{
	t_info	*info;
	int		id;
	int		meals_eaten;
	long	start_time_ms;
	long	time_of_last_meal;
	long	right_fork_timestamp_ms;
}	t_philo;

bool		convert_input(int argc, char **argv, t_info *p);
int			philo_atoi(const char *str, t_info *p);

long		time_in_ms(void);
long		time_in_usec(void);
long		usec_to_ms(long usec);
long		timestamp_in_ms(t_philo *philo);
void		set_start_time(t_philo *philo, t_info *i);

void		make_semaphores(t_info *info);
void		make_monitor(t_philo *philos, t_info *info);
pthread_t	make_times_eaten_monitor(t_info *info);
void		make_philos(t_philo *philo, t_info *info);

void		*starvation_monitor(void *philo);
void		*times_eaten_monitor(void *ptr_to_info);
void		life(t_philo *p, t_info *i);

void		sleep_till(long target_time_ms, t_philo *philo);
bool		print_action(long time, t_philo *philo, t_info *i, char *action);
void		kill_all_philos(t_info *info);

#endif