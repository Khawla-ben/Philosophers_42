/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:27 by kben-ham          #+#    #+#             */
/*   Updated: 2023/04/02 14:52:58 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void *arg)
{
	t_philo	*p;
	int		i;

	i = 0;
	p = arg;
	if (p->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&p->my_data->fork[p->l_fork]);
		my_print(p->my_data, "took the l_fork", p->id);
		pthread_mutex_lock(&(p->my_data->fork[p->r_fork]));
		my_print(p->my_data, "took the r_fork", p->id);
		my_print(p->my_data, "is eating", p->id);
		count(p);
		ft_usleep(p->my_data->t_eat);
		pthread_mutex_unlock(&(p->my_data->fork[p->l_fork]));
		pthread_mutex_unlock(&(p->my_data->fork[p->r_fork]));
		my_print(p->my_data, "is sleeping", p->id);
		ft_usleep(p->my_data->t_sleep);
		my_print(p->my_data, "is thinking", p->id);
	}
	return (NULL);
}

void	count(t_philo *p)
{
	pthread_mutex_lock(&p->my_data->time);
	p->last_t_eat = ft_time();
	(p->nb_repast)++;
	pthread_mutex_unlock(&p->my_data->time);
}

int	func2(t_data *my_data)
{
	int	i;

	i = 0;
	if (my_data->nb_t_to_eat == -1)
		return (1);
	while (i < my_data->nb_philo)
	{
		pthread_mutex_lock(&my_data->time);
		if (my_data->p[i].nb_repast < my_data->nb_t_to_eat)
		{
			pthread_mutex_unlock(&my_data->time);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&my_data->time);
	}
	return (0);
}

int	stop_function(t_data *my_data)
{
	int	i;

	while (func2(my_data))
	{
		i = 0;
		while (i < my_data->nb_philo)
		{
			pthread_mutex_lock(&my_data->time);
			if ((ft_time() - my_data->p[i].last_t_eat) >= (my_data->t_die))
			{
				my_print1(my_data, "is died", my_data->p[i].id);
				pthread_mutex_unlock(&my_data->time);
				return (0);
			}
			pthread_mutex_unlock(&my_data->time);
			i++;
		}
	}
	return (0);
}

void	all(t_data *my_data)
{
	int	j;

	j = 0;
	while (j < my_data->nb_philo)
	{
		my_data->p[j].last_t_eat = ft_time();
		if (pthread_create(&my_data->p[j].thread, NULL,
				thread_function, &my_data->p[j]) != 0)
		{
			write(2, "ERROR!", 6);
			return ;
		}
		pthread_detach(my_data->p[j].thread);
		j++;
	}
	stop_function(my_data);
	destroy(my_data);
}
