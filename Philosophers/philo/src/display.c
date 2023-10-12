/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrault <rrault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:19 by rrault            #+#    #+#             */
/*   Updated: 2023/10/12 12:25:38 by rrault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*get_message(int message)
{
	if (message == MESSAGE_FORK)
		return ("has taken a fork");
	if (message == MESSAGE_EAT)
		return ("is eating");
	if (message == MESSAGE_SLEEP)
		return ("is sleeping");
	if (message == MESSAGE_THINK)
		return ("is thinking");
	if (message == MESSAGE_DEATH)
		return ("\033[31mdied\n\033[0m");
	return ("Error: not valid msg id");
}

void	print_message(t_philo *philo, int message)
{
	size_t	t;

	t = get_elapsed_time() - philo->data->t_0;
	pthread_mutex_lock(&philo->data->display);
	if (!philo->data->death && !philo->data->eaten_meals)
	{
		printf("%ld ", t);
		printf(" %d ", philo->id);
		printf("%s", get_message(message));
		printf("\n");
	}
	pthread_mutex_unlock(&philo->data->display);
}
