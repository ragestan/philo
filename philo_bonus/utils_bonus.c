/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:42:59 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/18 18:44:34 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check(char **ag)
{
	int	i;
	int	j;

	i = 1;
	while (ag[i])
	{
		j = 0;
		while (ag[i][j])
		{
			if (ag[i][j] < '0' || ag[i][j] > '9')
				return (69);
			j++;
		}
		i++;
	}
	return (0);
}

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

int	test(t_philo ls, char **ag)
{
	if (ls.nbr_of_philos < 1 || ls.time_to_die <= 0 || ls.time_to_eat < 0
		|| ls.time_to_sleep < 0 || check(ag) == 69)
		return (69);
	else
		return (0);
}

long long	ft_atoi(const char *str)
{
	long long	c;
	int			i;

	i = 1;
	c = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			i = -i;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		c = c * 10 + *str++ - '0';
		if (c > INT_MAX)
			return (-69);
	}
	c = c * i;
	return (c);
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
		gettimeofday(&ls.philo[i].time_of_last_meal, NULL);
		ls.philo[i++].ls = &ls;
	}
	return (ls);
}
