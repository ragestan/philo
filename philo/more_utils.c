/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:47:52 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/16 13:01:19 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	ft_util(char **ag)
{
	t_philo	ls;

	ls.deth_check = 0;
	ls.nbr_of_philos = ft_atoi(ag[1]);
	ls.philo = malloc(sizeof(t_id) * ls.nbr_of_philos);
	ls.time_to_die = ft_atoi(ag[2]);
	ls.time_to_eat = ft_atoi(ag[3]);
	ls.time_to_sleep = ft_atoi(ag[4]);
	ls.first = get_time();
	ls.timer_start = get_time();
	if (ag[5])
		ls.nbr_of_must_eat = ft_atoi(ag[5]);
	else
		ls.nbr_of_must_eat = -69;
	return (ls);
}

t_philo	ft_util2(t_philo ls, int i)
{
	while (i < ls.nbr_of_philos)
	{
		ls.philo[i].meal_count = 0;
		ls.philo[i].nbr_of_must_eat = ls.nbr_of_must_eat;
		ls.philo[i].timer_start = ls.timer_start;
		ls.philo[i].time_to_sleep = ls.time_to_sleep;
		ls.philo[i].time_to_eat = ls.time_to_eat;
		ls.philo[i].id = i + 1;
		ls.philo[i].left_fork_id = i + 1;
		ls.philo[i].right_fork_id = (i + 1) % ls.nbr_of_philos;
		ls.philo[i].right_philo = &ls.philo[(i + 1) % ls.nbr_of_philos];
		ls.philo[i].time_of_last_meal = 0;
		ls.philo[i++].ls = &ls;
	}
	return (ls);
}

int	test(t_philo ls, char **ag)
{
	if (ls.nbr_of_philos < 1 || ls.time_to_die <= 0 || ls.time_to_eat < 0
		|| ls.time_to_sleep < 0 || check(ag) == 69)
		return (69);
	else
		return (0);
}

int	creat(t_id *new, t_philo ls, int i)
{
	while (++i <= ls.nbr_of_philos)
	{
		if (pthread_create(&(new[i].new), NULL, yaya, &new[i]) != 0)
			return (0);
		pthread_detach((new[i].new));
	}
	return (0);
}

int	deth_check(t_philo ls)
{
	int	i;

	while (ls.deth_check == 0)
	{
		i = 0;
		while (i < ls.nbr_of_philos)
		{
			pthread_mutex_lock(&ls.eat);
			if (get_time() - ls.timer_start
				- ls.philo[i].time_of_last_meal > ls.time_to_die)
			{
				ls.deth_check = 1;
				printf("%li %i died\n", get_time() - ls.timer_start, i);
				break ;
			}
			i++;
			pthread_mutex_unlock(&ls.eat);
			usleep(1000);
		}
		if (ls.deth_check == 1)
			break ;
		if (ft_check_if_philo_are_full(&ls) == 69)
			break ;
	}
	return (0);
}
