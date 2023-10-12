/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrault <rrault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:13 by rrault            #+#    #+#             */
/*   Updated: 2023/10/12 11:28:05 by rrault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_mange(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->fork);
	print_message(philo, MESSAGE_FORK);
	if (philo->data->nbr_philos == 1)
	{
		ft_usleep(data, data->time_to_die);
		print_message(philo, MESSAGE_DEATH);
		pthread_mutex_unlock(&philo->fork);
		data->death = 1;
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	print_message(philo, MESSAGE_FORK);
	pthread_mutex_lock(&data->check);
	philo->nbr_eat++;
	print_message(philo, MESSAGE_EAT);
	philo->last_meal = get_elapsed_time();
	pthread_mutex_unlock(&data->check);
	ft_usleep(data, data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*cycle_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!data->death && !data->eaten_meals)
	{
		philo_mange(philo);
		print_message(philo, MESSAGE_SLEEP);
		ft_usleep(data, data->time_to_sleep);
		print_message(philo, MESSAGE_THINK);
	}
	return (NULL);
}
