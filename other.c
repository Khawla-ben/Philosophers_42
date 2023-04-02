/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 02:50:23 by kben-ham          #+#    #+#             */
/*   Updated: 2023/04/02 14:33:50 by kben-ham         ###   ########.fr       */
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

long long	ft_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * 1000ll) + (tm.tv_usec / 1000ll));
}

void	my_print(t_data *my_data, char *test, int id)
{
	pthread_mutex_lock(&my_data->write);
	printf("%lld %d %s\n", ft_time() - my_data->t_beginning, id, test);
	pthread_mutex_unlock(&my_data->write);
}

void	my_print1(t_data *my_data, char *test, int id)
{
	pthread_mutex_lock(&my_data->write);
	printf("%lld %d %s\n", ft_time() - my_data->t_beginning, id, test);
}

void	destroy(t_data *my_data)
{
	int	j;

	j = -1;
	while (++j < my_data->nb_philo)
		pthread_mutex_destroy(&my_data->fork[j]);
	pthread_mutex_destroy(&my_data->write);
	pthread_mutex_destroy(&my_data->time);
}
