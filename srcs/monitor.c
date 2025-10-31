/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* monitor.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/* localVarHTTP   +#+           */
/* Created: 2025/10/31 00:30:00 by ruben             #+#    #+#             */
/* Updated: 2025/10/31 00:30:00 by ruben            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Comprueba si algún filósofo ha muerto.
 *
 * @param sim La estructura de simulación.
 * @return 1 si alguien murió, 0 si no.
 */
static int	check_death(t_sim *sim)
{
	int		i;
	long	current_time;

	i = 0;
	current_time = get_current_time();
	while (i < sim->num_philos)
	{
		// Protegemos la lectura de 'last_meal_time'
		pthread_mutex_lock(&sim->sim_mutex);
		if (current_time - sim->philos[i].last_meal_time >= sim->time_to_die)
		{
			// ¡Muerto!
			// Ponemos el flag para que todos paren
			sim->simulation_should_end = 1;
			pthread_mutex_unlock(&sim->sim_mutex);

			// Imprimimos el mensaje de muerte (con su propio mutex)
			print_status(&sim->philos[i], "died", 1);
			return (1); // 1 = Alguien murió
		}
		pthread_mutex_unlock(&sim->sim_mutex);
		i++;
	}
	return (0); // 0 = Nadie murió
}

/**
 * @brief Comprueba si todos los filósofos han comido 'num_meals_to_eat'.
 *
 * @param sim La estructura de simulación.
 * @return 1 si todos comieron, 0 si no.
 */
static int	check_meals(t_sim *sim)
{
	int	i;
	int	all_have_eaten;

	// Si el argumento no se dio (es -1), saltamos esta comprobación
	if (sim->num_meals_to_eat == -1)
		return (0);
	i = 0;
	all_have_eaten = 1; // Asumimos que es verdad
	while (i < sim->num_philos)
	{
		// Protegemos la lectura de 'meals_eaten'
		pthread_mutex_lock(&sim->sim_mutex);
		if (sim->philos[i].meals_eating < sim->num_meals_to_eat)
			all_have_eaten = 0; // Encontramos uno que no ha comido
		pthread_mutex_unlock(&sim->sim_mutex);
		i++;
	}
	if (all_have_eaten)
	{
		// ¡Todos comieron!
		pthread_mutex_lock(&sim->sim_mutex);
		sim->simulation_should_end = 1; // Ponemos el flag para parar
		pthread_mutex_unlock(&sim->sim_mutex);
		return (1); // 1 = Todos comieron
	}
	return (0); // 0 = Aún no
}

/**
 * @brief La rutina del hilo monitor (el vigilante).
 *
 * Comprueba constantemente si la simulación debe terminar
 * (por muerte o por número de comidas).
 */
void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	// El monitor se ejecuta mientras la simulación DEBA continuar
	while (1)
	{
		// Comprobación de estado (protegida)
		pthread_mutex_lock(&sim->sim_mutex);
		if (sim->simulation_should_end)
		{
			pthread_mutex_unlock(&sim->sim_mutex);
			break; // Salir si ya alguien activó el flag
		}
		pthread_mutex_unlock(&sim->sim_mutex);

		// 1. ¿Alguien ha muerto?
		if (check_death(sim))
			break; // Si sí, salimos del bucle
		// 2. ¿Han comido todos?
		if (check_meals(sim))
			break; // Si sí, salimos del bucle
		
		// Dormimos un poco para no quemar la CPU
		usleep(1000); // Chequeamos cada 1ms
	}
	return (NULL);
}