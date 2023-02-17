/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:07:16 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/17 17:54:51 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_id
{
	int				id;
	time_t			timer_start;
	int				left_fork_id;
	int				right_fork_id;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_must_eat;
	int				meal_count;
	time_t			time_of_last_meal;
	time_t			time_of_start_sleep;
	pthread_t		new;
	struct s_id		*right_philo;
	struct s_philo	*ls;
}					t_id;

typedef struct s_philo
{
	time_t			timer_start;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_must_eat;
	long long		first;
	int				deth_check;
	sem_t			*forks;
	sem_t			*g;
	t_id			*philo;
}					t_philo;

void				one_philo(t_id *new);
time_t				get_time(void);
time_t				get_time_us(struct timeval end, struct timeval start);
void				eat_timer(time_t time);
void				sleep_timer(t_id new);
int					check(char **ag);
int					test(t_philo ls, char **ag);
t_philo				ft_util(char **ag);
t_philo				ft_util2(t_philo ls, int i);
long long			ft_atoi(const char *str);
#endif