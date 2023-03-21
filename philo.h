/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:49:05 by kben-ham          #+#    #+#             */
/*   Updated: 2023/03/19 18:45:26 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_data
{
	int nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_t_to_eat;
	int t_beginning;
	struct each_philo *p;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
	
}t_data;

typedef struct each_philo
{
	int id;
	int last_t_eat;
	int nb_repast;
	int	l_fork;
	int	r_fork;
	// int	/die ;
	t_data *my_data;
	pthread_t thread;
	
	
	

	
}t_philo;

void create_threads(char **av, int ac);
void initialize_data(char **av, t_data *my_data, int ac);
int	ft_atoi(char *str);
long long	ft_time(void);
void 	initialize_philo(t_data *my_data);
void initialize_mutex(t_data *my_data);
void *thread_function(void *arg);
#endif