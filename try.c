
#include "philo.h"

void    ft_usleep(long long var)
{
    long long    time;
    time = ft_time();
    while (ft_time() - time < var)
        usleep(100);
}

void *thread_function(void *arg)
{
	t_philo *p;
	int i;

	i = 0;
	p = arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		// puts("dfbb");
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

void	initialize_data(char **av, t_data *my_data, int ac)
{
	my_data->nb_philo = ft_atoi(av[1]);
	my_data->t_die = ft_atoi(av[2]);
	my_data->t_eat = ft_atoi(av[3]);
	my_data->t_sleep = ft_atoi(av[4]);
	my_data->die = 0;
	if (ac == 6)
		my_data->nb_t_to_eat = ft_atoi(av[5]);
	else 
		my_data->nb_t_to_eat = -1;

}

void initialize_mutex(t_data *my_data)
{
	int	j;

	j = 0;
	my_data->fork = malloc(sizeof(pthread_mutex_t) * my_data->nb_philo + 2);
	if(!my_data->fork)
		return ;
	while (j < my_data->nb_philo)
	{
		if (pthread_mutex_init(&my_data->fork[j++], NULL) != 0)
			return ;
	}
	if (pthread_mutex_init(&my_data->write, NULL) != 0)
		return ;
	if (pthread_mutex_init(&my_data->time ,NULL) != 0)
		return ;
}

void 	initialize_philo(t_data *my_data)
{
	int	j;

	j = 0;
	my_data->p = malloc(sizeof(struct each_philo) * my_data->nb_philo);
	if(!my_data->p)
		return ;
	while (j < my_data->nb_philo)
	{
		my_data->p[j].id = j + 1;
		my_data->p[j].nb_repast = 0;
		my_data->p[j].l_fork = j;
		my_data->p[j].r_fork = (j - 1) % my_data->nb_philo ;
		my_data->p[j].my_data = my_data;
		j++;
	}
}

long long	ft_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * 1000ll) + (tm.tv_usec / 1000ll));
}

void create_threads(char **av, int ac)
{
	t_data	*my_data;
	int j;

	j = 0;
	my_data = malloc (sizeof(t_data));
	my_data->t_beginning = ft_time();
	initialize_data(av, my_data, ac);
	initialize_mutex(my_data);
	initialize_philo(my_data);

	while (j < my_data->nb_philo)
	{
		my_data->p[j].last_t_eat  = ft_time();
		if (pthread_create(&my_data->p[j].thread, NULL, thread_function, &my_data->p[j]) != 0)
		{
			write(1, "ERROR!", 6);
			return ;
		}
		pthread_detach(my_data->p[j].thread);
		j++;
	}
	while (1)
	
}
