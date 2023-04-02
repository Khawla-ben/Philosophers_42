/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:56:27 by kben-ham          #+#    #+#             */
/*   Updated: 2023/04/02 02:23:09 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long tmp)
{
	long long	t;

	t = ft_time();
	while (ft_time() - t < tmp)
		usleep(100);
}

void	*thread_function(void *arg)
{
	t_philo	*p;
	int	i;

	i = 0;
	p = arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&p->my_data->fork[p->l_fork]);
		pthread_mutex_lock(&p->my_data->write);
		printf("%lld %d %s\n", ft_time() - p->my_data->t_beginning, p->id, "took the l_fork");
		pthread_mutex_unlock(&p->my_data->write);

		pthread_mutex_lock(&(p->my_data->fork[p->r_fork]));
		pthread_mutex_lock(&p->my_data->write);
		printf("%lld %d %s\n", ft_time() - p->my_data->t_beginning, p->id, "took the r_fork");
		pthread_mutex_unlock(&p->my_data->write);

		pthread_mutex_lock(&p->my_data->write);
		printf("%lld %d %s\n", ft_time() - p->my_data->t_beginning, p->id, "is eating");
		pthread_mutex_unlock(&p->my_data->write);

		pthread_mutex_lock(&p->my_data->time);
		p->last_t_eat = ft_time();
		(p->nb_repast)++;
		pthread_mutex_unlock(&p->my_data->time);
		ft_usleep(p->my_data->t_eat);

		pthread_mutex_unlock(&(p->my_data->fork[p->l_fork]));
		pthread_mutex_unlock(&(p->my_data->fork[p->r_fork]));

		pthread_mutex_lock(&p->my_data->write);
		printf("%lld %d %s\n", ft_time() - p->my_data->t_beginning, p->id, "is sleeping");
		pthread_mutex_unlock(&p->my_data->write);
		ft_usleep(p->my_data->t_sleep);

		pthread_mutex_lock(&p->my_data->write);
		printf("%lld %d %s\n", ft_time() - p->my_data->t_beginning, p->my_data->nb_philo, "is thinking");
		pthread_mutex_unlock(&p->my_data->write);
	}
	return (NULL);
}

long long	ft_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * 1000ll) + (tm.tv_usec / 1000ll));
}

int func2(t_data *my_data)
{
	int i;
	
	i = 0;
	if (my_data->nb_t_to_eat == -1)
		return (1);
	while (i < my_data->nb_philo)
	{
		if (my_data->p[i].nb_repast < my_data->nb_t_to_eat)//////////ookokok
			return (1);
		i++;
	}
	return (0);
}

int stop_function(t_data *my_data)
{
	int i;

	while (func2(my_data))
	{
		i = 0;
		while (i < my_data->nb_philo)
		{
			if ((ft_time() - my_data->p[i].last_t_eat) >= (my_data->t_die))//////////ookokok
			{
				pthread_mutex_lock(&my_data->write);
				printf("%lld %d %s\n", ft_time() - my_data->t_beginning, my_data->p[i].id, "is died");
				pthread_mutex_unlock(&my_data->write);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

void	create_threads(char **av, int ac)
{
	t_data	*my_data;
	int	j;

	j = 0;
	my_data = malloc (sizeof(t_data));
	if(!my_data)
		return ;
	my_data->t_beginning = ft_time();
	initialize_data(av, my_data, ac);
	initialize_mutex(my_data);
	initialize_philo(my_data);
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
	j = -1;
	while (++j < my_data->nb_philo)
		pthread_mutex_destroy(&my_data->fork[j]);
	pthread_mutex_destroy(&my_data->write);
	pthread_mutex_destroy(&my_data->time);
	return ;
}