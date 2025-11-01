/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* actions.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/* localVarHTTP   +#+           */
/* Created: 2025/10/31 14:30:00 by ruben             #+#    #+#             */
/* Updated: 2025/10/31 14:30:00 by ruben            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Suelta los tenedores (mutexes) en el orden correcto.
 */
static void	drop_forks(t_philo *philo)
{
	// El orden de soltar no importa para el deadlock,
	// pero por simetría, los soltamos.
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/**
 * @brief Coge los tenedores usando la lógica par/impar para evitar deadlocks.
 */
static void	take_forks(t_philo *philo)
{
	// Lógica Anti-Deadlock (Par/Impar)
	if (philo->id % 2 == 0) // Filósofo PAR
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", 0);
	}
	else // Filósofo IMPAR
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", 0);
	}
}

/**
 * @brief Acción de COMER.
 */
void	philo_eat(t_philo *philo)
{
	// 1. Coger tenedores (con lógica anti-deadlock)
	take_forks(philo);

	// 2. Actualizar estado y comer
	pthread_mutex_lock(&philo->sim->sim_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eating++;
	pthread_mutex_unlock(&philo->sim->sim_mutex);

    print_status(philo, "is eating", 0);

	precise_usleep(philo->sim->time_to_eat, philo->sim);

	// 3. Soltar tenedores
	drop_forks(philo);
}

/**
 * @brief Acción de DORMIR.
 */
void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping", 0);
	precise_usleep(philo->sim->time_to_sleep, philo->sim);
}

/**
 * @brief Acción de PENSAR.
 */
void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking", 0);
	// Nota: Un pequeño 'sleep' aquí puede ayudar a
	// desincronizar a los filósofos, especialmente con números pares.
	usleep(500);
}