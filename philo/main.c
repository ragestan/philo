/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:53:52 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/19 18:21:28 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_id *new)
{
	printf("%li %i has taken a fork \n", get_time() - new->timer_start,
		new->id);
}

int	main(int ac, char **ag)
{
	t_philo	ls;
	t_id	*new;
	int		i;

	if (ac != 5 && ac != 6)
		return (write(1, "Wrong number of argument\n", 26), 1);
	ls = ft_util(ag);
	if (test(ls, ag) == 69)
		return (write(1, "at least 1 Wrong argument!\n", 28), 1);
	i = ls.nbr_of_philos - 1;
	while (i >= 0)
		pthread_mutex_init(&ls.philo[i--].forks, NULL);
	pthread_mutex_init(&ls.write, NULL);
	pthread_mutex_init(&ls.eat, NULL);
	ls = ft_util2(ls, 0);
	new = ls.philo;
	creat(new, ls, i);
	deth_check(ls);
	i = ls.nbr_of_philos;
	while (i > 0)
	{
		pthread_mutex_destroy(&ls.philo[i--].forks);
	}
	pthread_mutex_destroy(&ls.eat);
	pthread_mutex_destroy(&ls.write);
}
