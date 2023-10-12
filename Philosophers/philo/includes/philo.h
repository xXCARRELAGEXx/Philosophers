/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrault <rrault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:24:45 by rrault            #+#    #+#             */
/*   Updated: 2023/10/12 12:25:10 by rrault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_msg
{
	MESSAGE_FORK = 0,
	MESSAGE_EAT,
	MESSAGE_SLEEP,
	MESSAGE_THINK,
	MESSAGE_DEATH
};

typedef struct s_philo
{
	int				id;
	int				nbr_eat;
	size_t			last_meal;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*last;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
	int				nbr_philos;
	int				eaten_meals;
	int				death;
	size_t			t_0;
	t_philo			*philos;
	pthread_mutex_t	die;
	pthread_mutex_t	display;
	pthread_mutex_t	check;
}					t_data;

int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					check_args(int argc, char *argv[], t_data *data);
void				print_message(t_philo *philo, int message);
void				*cycle_life(void *arg);
void				check_death(t_data *data);
void				ft_exit(t_data *data, pthread_t *id);
size_t				get_elapsed_time(void);
void				ft_usleep(t_data *data, size_t time);

#endif
