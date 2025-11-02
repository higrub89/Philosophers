/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:56:43 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 14:51:33 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_sim *sim)
{
	int	i;

	if (sim->num_meals_to_eat == -1)
		return (0);
	i = 0;
	while (i < sim->num_philos)
	{
		if (sim->philos[i].meals_eating < sim->num_meals_to_eat)
			return (0);
		i++;
	}
	sim->simulation_should_end = 1;
	return (1);
}

static int	check_philos_death(t_sim *sim, long current_time)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (current_time - sim->philos[i].last_meal_time >= sim->time_to_die)
		{
			sim->simulation_should_end = 1;
			pthread_mutex_unlock(&sim->sim_mutex);
			print_status(&sim->philos[i], "died", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_death_and_meals(t_sim *sim)
{
	long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&sim->sim_mutex);
	if (sim->simulation_should_end)
	{
		pthread_mutex_unlock(&sim->sim_mutex);
		return (1);
	}
	if (check_meals(sim))
	{
		pthread_mutex_unlock(&sim->sim_mutex);
		return (1);
	}
	if (check_philos_death(sim, current_time))
		return (1);
	pthread_mutex_unlock(&sim->sim_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	usleep(sim->time_to_die / 2 * 1000);
	while (1)
	{
		if (check_death_and_meals(sim))
			break ;
		usleep(1000);
	}
	return (NULL);
}
