/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:34:16 by kben-ham          #+#    #+#             */
/*   Updated: 2023/03/26 14:59:13 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32 && str[i]))
		i++;
	
	if (str[0] == '-')
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	while (str[i] && (ft_isdigit(str[i]) == 1))
		n = (n * 10 + (str[i++] - 48));
	if ((n > 2147483647) || (n == 0) || (ft_isdigit(str[i]) == 0 && str[i]))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (n);
}

void parcing(int ac, char **av)
{
	int i;

	i = ac - 1;
	while (i > 0)
		ft_atoi(av[i--]);
}

int main(int ac, char **av)
{
	if (ac == 6 || ac == 5)
	{
		parcing(ac, av);
		create_threads(av, ac);
	}
	else
		write(1, "INVALID ARGS\n",14);
	return (0);
}