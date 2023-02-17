/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:42:18 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/16 13:03:27 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_id	*ls_norm(t_id *new)
{
	pthread_mutex_lock(&new->ls->write);
	new->meal_count++;
	pthread_mutex_unlock(&new->ls->write);
	return (new);
}

void	*yaya(void *kekw)
{
	t_id	*new;

	new = (t_id *)kekw;
	if (!(new->id % 2))
		usleep(1000);
	while (new->meal_count != new->nbr_of_must_eat)
	{	
		pthread_mutex_lock(&new->forks);
		ft_print(new);
		pthread_mutex_lock(&new->right_philo->forks);
		ft_print(new);
		pthread_mutex_lock(&new->ls->eat);
		printf("%li %i is eating\n", get_time() - new->timer_start, new->id);
		new->time_of_last_meal = get_time() - new->timer_start;
		pthread_mutex_unlock(&new->ls->eat);
		new = ls_norm(new);
		eat_timer(new->time_to_eat);
		pthread_mutex_unlock(&new->forks);
		pthread_mutex_unlock(&new->right_philo->forks);
		printf("%li %i is sleeping\n", get_time() - new->timer_start, new->id);
		new->time_of_start_sleep = get_time();
		eat_timer(new->time_to_sleep);
		printf("%li %i is thinking\n", get_time() - new->timer_start, new->id);
	}
	return (NULL);
}

int	ft_check_if_philo_are_full(t_philo *new)
{
	int	i;
	int	j;

	pthread_mutex_lock(&new->write);
	i = new->nbr_of_philos - 1;
	j = 0;
	if (new->nbr_of_must_eat == -69)
	{
		pthread_mutex_unlock(&new->write);
		return (0);
	}
	while (i >= 0)
	{
		if (new->philo[i--].meal_count == new->nbr_of_must_eat)
			j++;
	}
	if (j == new->nbr_of_philos)
		return (69);
	pthread_mutex_unlock(&new->write);
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
