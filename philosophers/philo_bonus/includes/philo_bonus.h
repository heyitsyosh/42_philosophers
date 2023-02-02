/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:43:21 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/03 04:13:48 by myoshika         ###   ########.fr       */
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
# define SEM_MIN_REQ "ate_minimum_requirement"
# define SEM_STOP "sem_stop_simulation"

typedef struct s_info{
	int			num_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			meals_to_eat;
	sem_t		*sem_print;
	sem_t		**sem_lock;
	sem_t		*forks;
	sem_t		*ate_minimum_req;
	sem_t		*stop_simulation;
	bool		overflow;
	pid_t		*philo_pid;
	pthread_t	times_eaten_monitor_tid;
	pthread_t	stop_simulation_monitor_tid;
}	t_info;

typedef struct s_philo{
	t_info		*info;
	int			id;
	int			meals_eaten;
	long		start_time_ms;
	long		time_of_last_meal;
	long		right_fork_timestamp_ms;
}	t_philo;

long	time_in_ms(void);
long	time_in_usec(void);
long	timestamp_in_ms(t_philo *philo);

int		philo_atoi(const char *str, t_info *p);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	set_start_time(t_philo *philo, t_info *i);
void	sleep_till(long target_time_ms, t_philo *philo);
void	print_action(long time, t_philo *philo, t_info *info, char *action);
void	print_error_and_exit(char *error_message);
void	kill_all_philos(t_info *info);

bool	convert_input(int argc, char **argv, t_info *p);
void	make_semaphores(t_info *info);
void	make_philos(t_philo *philo, t_info *info);
void	make_starvation_monitor(t_philo *philo, t_info *info);
void	make_times_eaten_monitor(t_info *info);
void	make_stop_simulation_monitor(t_info *info);
void	wait_for_monitors_to_detect(t_info *info);

void	life(t_philo *p, t_info *i);
void	*starvation_monitor(void *philo);
void	*times_eaten_monitor(void *ptr_to_info);
void	*stop_simulation_monitor(void *ptr_to_info);

#endif