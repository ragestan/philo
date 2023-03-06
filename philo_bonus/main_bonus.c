/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:23:13 by zbentalh          #+#    #+#             */
/*   Updated: 2023/02/19 19:11:43 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_id *new)
{
	sem_wait(new->ls->print);
	printf("%li %i has taken a fork \n", get_time() - new->timer_start,
		new->id);
	sem_post(new->ls->print);
}

void	*yaya(void *kekw)
{
	t_id	*new;

	new = (t_id *)kekw;
	if (!(new->id % 2))
		usleep(1000);
	while (1)
	{
		sem_wait(new->ls->forks);
		(ft_print(new), sem_wait(new->ls->forks), ft_print(new));
		(sem_wait(new->ls->g), gettimeofday(&new->time_of_last_meal, NULL));
		new->meal_count++;
		sem_wait(new->ls->print);
		printf("%li %i is eating\n", get_time() - new->timer_start, new->id);
		(sem_post(new->ls->print), sem_post(new->ls->g));
		(eat_timer(new->time_to_eat), sem_post(new->ls->forks));
		(sem_post(new->ls->forks), sem_wait(new->ls->print));
		if (new->meal_count == new->nbr_of_must_eat)
			(sem_post(new->ls->print), exit(0));
		printf("%li %i is sleeping\n", get_time() - new->timer_start, new->id);
		(sem_post(new->ls->print), eat_timer(new->time_to_sleep));
		(sem_wait(new->ls->print), printf("%li %i is thinking\n", get_time()
				- new->timer_start, new->id), sem_post(new->ls->print));
	}
	return (NULL);
}

void	ft_philo(t_id *new, t_philo *ls, int i)
{
	struct timeval	curr;

	pthread_create(&(new[i].new), NULL, yaya, &new[i]);
	pthread_detach((new[i].new));
	while (1)
	{
		gettimeofday(&curr, NULL);
		sem_wait(new->ls->g);
		if (get_time_us(curr, new[i].time_of_last_meal) > ls->time_to_die)
		{
			sem_wait(new->ls->print);
			printf("%li %i died\n", get_time() - new[i].ls->timer_start,
				new[i].ls->philo[i].id);
			exit(ls->philo[i].id);
		}
		sem_post(new->ls->g);
		usleep(200);
	}
}

void	ft_norm(int i, t_philo *ls, int *z, t_id *new)
{
	int	status;

	while (i < ls->nbr_of_philos)
	{
		z[i] = fork();
		if (z[i] == 0)
			ft_philo(new, ls, i);
		else
			i++;
	}
	i = 1;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 0)
	{
		while (i < ls->nbr_of_philos)
		{
			waitpid(-1, &status, 0);
			if (WEXITSTATUS(status) != 0)
				break ;
			i++;
		}
	}
	i = 0;
	while (i < ls->nbr_of_philos)
		kill(z[i++], SIGTERM);
}

int	main(int ac, char **ag)
{
	t_philo	ls;
	t_id	*new;
	int		i;
	int		*z;

	if (ac != 5 && ac != 6)
		return (write(1, "Wrong number of argument\n", 26), 1);
	ls = ft_util(ag);
	if (test(ls, ag) == 69)
		return (write(1, "at least 1 Wrong argument!\n", 28), 1);
	z = malloc(sizeof(int) * ls.nbr_of_philos);
	i = 0;
	(sem_unlink("g"), sem_unlink("forks"), sem_unlink("print"));
	ls.forks = sem_open("forks", O_CREAT, 0644, ls.nbr_of_philos);
	ls.g = sem_open("g", O_CREAT, 0644, 1);
	ls.print = sem_open("print", O_CREAT, 0644, 1);
	if (ls.g == SEM_FAILED || ls.print == SEM_FAILED || ls.forks == SEM_FAILED)
		exit(1);
	ls = ft_util2(ls, 0);
	new = ls.philo;
	ft_norm(i, &ls, z, new);
}
