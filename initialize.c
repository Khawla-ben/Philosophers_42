/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:55:58 by kben-ham          #+#    #+#             */
/*   Updated: 2023/04/02 14:50:42 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(char **av, t_data *my_data, int ac)
{
	my_data->nb_philo = ft_atoi(av[1]);
	my_data->t_die = ft_atoi(av[2]);
	my_data->t_eat = ft_atoi(av[3]);
	my_data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		my_data->nb_t_to_eat = ft_atoi(av[5]);
	else
		my_data->nb_t_to_eat = -1;
}

void	initialize_mutex(t_data *my_data)
{
	int	j;

	j = 0;
	my_data->fork = malloc(sizeof(pthread_mutex_t) * my_data->nb_philo);
	if (!my_data->fork)
		return ;
	while (j < my_data->nb_philo)
	{
		if (pthread_mutex_init(&my_data->fork[j++], NULL) != 0)
			return ;
	}
	if (pthread_mutex_init(&my_data->write, NULL) != 0)
		return ;
	if (pthread_mutex_init(&my_data->time, NULL) != 0)
		return ;
}

void	initialize_philo(t_data *my_data)
{
	int	j;

	j = 0;
	my_data->p = malloc(sizeof(struct each_philo) * my_data->nb_philo);
	if (!my_data->p)
		return ;
	while (j < my_data->nb_philo)
	{
		my_data->p[j].id = j + 1;
		my_data->p[j].nb_repast = 0;
		my_data->p[j].l_fork = j;
		my_data->p[j].r_fork = (j + 1) % my_data->nb_philo ;
		my_data->p[j].my_data = my_data;
		j++;
	}
}
