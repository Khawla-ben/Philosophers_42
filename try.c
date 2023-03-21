
#include "philo.h"

void *thread_function(void *arg)
{
	t_data my_data;

	// while()
	if (my_data.p->id % 2 != 0)
		
		
	// puts("dsvds");
	// int thread_num = *((int*)arg);
	// printf("i'm the philo num : %d", thread_num);
	// // pthread_mutex_lock(&fork);
	// // pthread_mutex_unlock(&fork);

	return (NULL);
}

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

void initialize_mutex(t_data *my_data)
{
	int	j;

	j = 0;
	my_data->fork = malloc(sizeof(pthread_mutex_t) * my_data->nb_philo);
	while (j < my_data->nb_philo)
		pthread_mutex_init(&my_data->fork[j++], NULL);
	pthread_mutex_init(&my_data->write, NULL);

}

void 	initialize_philo(t_data *my_data)
{
	int	j;

	j = 0;
	my_data->p = malloc(sizeof(struct each_philo) * my_data->nb_philo);
	while (j < my_data->nb_philo)
	{
		my_data->p[j].id = j + 1;
		my_data->p[j].l_fork = j;
		my_data->p[j].nb_repast = 0;
		my_data->p[j].r_fork = (j - 1) % my_data->nb_philo ;
		my_data->p[j].my_data = my_data;
		j++;
	}
}

long long	ft_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void create_threads(char **av, int ac)
{
	t_data	my_data;
	int j;

	j = 0;
	initialize_data(av, &my_data, ac);
	initialize_mutex(&my_data);
	initialize_philo(&my_data);
	my_data.t_beginning = ft_time();

	while(j < my_data.nb_philo)
	{
		if (pthread_create(&my_data.p[j].thread, NULL, thread_function, &my_data.p[j].thread) != 0)
		{
			write(1, "ERROR!", 6);
			return ;
		}
		pthread_detach(my_data.p[j].thread);
		j++;
	}

}
