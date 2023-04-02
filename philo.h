/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:49:05 by kben-ham          #+#    #+#             */
/*   Updated: 2023/04/02 03:23:31 by kben-ham         ###   ########.fr       */
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
	int					nb_philo;
	int					t_eat;
	int					t_sleep;
	int					nb_t_to_eat;
	long long			t_die;
	long long			t_beginning;
	struct each_philo	*p;
	pthread_mutex_t		write;
	pthread_mutex_t		*fork;
	pthread_mutex_t		time;
}t_data;

typedef struct each_philo
{
	int			id;
	int			nb_repast;
	int			l_fork;
	int			r_fork;
	long long	last_t_eat;
	t_data		*my_data;
	pthread_t	thread;
}t_philo;

void		create_threads(char **av, int ac);
void		initialize_data(char **av, t_data *my_data, int ac);
void		initialize_philo(t_data *my_data);
void		initialize_mutex(t_data *my_data);
void		*thread_function(void *arg);
void		ft_usleep(long long tmp);
void		my_printf(t_data *my_data, char *test, int id);
void		count(t_philo *p);
void		destroy(t_data *my_data);
void		all(t_data *my_data);
int			stop_function(t_data *my_data);
int			ft_atoi(char *str);
long long	ft_time(void);

#endif