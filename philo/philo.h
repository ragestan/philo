/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:02:11 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/14 14:43:13 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
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
	pthread_mutex_t	forks;
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
	pthread_mutex_t	eat;
	pthread_mutex_t	write;
	t_id			*philo;
}					t_philo;

void				ft_print(t_id *new);
void				one_philo(t_id *new);
void				sleep_timer(t_id new);
void				eat_timer(time_t time);
time_t				get_time_us(struct timeval end, struct timeval start);
time_t				get_time(void);
int					ft_check_if_philo_are_full(t_philo *new);
void				*yaya(void *kekw);
long long			ft_atoi(const char *str);
int					check(char **ag);
t_philo				ft_util2(t_philo ls, int i);
t_philo				ft_util(char **ag);
int					deth_check(t_philo ls);
int					creat(t_id *new, t_philo ls, int i);
int					test(t_philo ls, char **ag);
#endif