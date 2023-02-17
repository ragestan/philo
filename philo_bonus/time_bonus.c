/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:49:34 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/16 13:45:41 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_philo(t_id *new)
{
	if (new->ls->nbr_of_philos == 1)
	{
		eat_timer(new->ls->time_to_die);
		eat_timer(new->ls->time_to_die);
	}
	return ;
}

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

time_t	get_time_us(struct timeval end, struct timeval start)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000
			+ start.tv_usec / 1000));
}

void	eat_timer(time_t time)
{
	struct timeval	end;
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		if (get_time_us(end, start) >= time)
			break ;
		usleep(100);
	}
}

void	sleep_timer(t_id new)
{
	time_t	time;

	time = (time_t)get_time - (time_t) new.time_of_start_sleep;
	while (time <= new.time_to_sleep)
	{
		time = get_time() - new.time_of_start_sleep;
		usleep(100);
	}
	return ;
}
