/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* monitor.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/* localVarHTTP   +#+           */
/* Created: 2025/10/31 00:30:00 by ruben             #+#    #+#             */
/* Updated: 2025/11/01 10:20:00 by ruben            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Comprueba si todos los filósofos han comido 'num_meals_to_eat'.
 *
 * ¡¡VERSIÓN OPTIMIZADA!!
 * Esta función DEBE ser llamada MIENTRAS sim_mutex ESTÁ BLOQUEADO.
 *
 * @param sim La estructura de simulación.
 * @return 1 si todos comieron, 0 si no.
 */
static int	check_meals(t_sim *sim)
{
	int	i;

	if (sim->num_meals_to_eat == -1)
		return (0);
	i = 0;
	while (i < sim->num_philos)
	{
		// Asumimos que sim_mutex ya está bloqueado
		if (sim->philos[i].meals_eating < sim->num_meals_to_eat)
			return (0); // Encontramos uno que no ha comido, salimos
		i++;
	}
	// Si salimos del bucle, es que todos comieron
	sim->simulation_should_end = 1; // Ponemos el flag para parar
	return (1); // 1 = Todos comieron
}

/**
 * @brief Comprueba si algún filósofo ha muerto.
 *
 * ¡¡VERSIÓN OPTIMIZADA!!
 * Bloquea sim_mutex UNA SOLA VEZ para comprobar a todos.
 *
 * @param sim La estructura de simulación.
 * @return 1 si alguien murió, 0 si no.
 */
static int	check_death_and_meals(t_sim *sim)
{
	int		i;
	long	current_time;

	i = 0;
	current_time = get_current_time();

	// ---- INICIO SECCIÓN CRÍTICA (¡UNA SOLA VEZ!) ----
	pthread_mutex_lock(&sim->sim_mutex);
	
	// 1. Comprobar si ya debemos parar (por si acaso)
	if (sim->simulation_should_end)
	{
		pthread_mutex_unlock(&sim->sim_mutex);
		return (1);
	}

	// 2. Comprobar si todos han comido
	if (check_meals(sim))
	{
		pthread_mutex_unlock(&sim->sim_mutex);
		return (1); // check_meals ya puso el flag
	}

	// 3. Comprobar muertes
	while (i < sim->num_philos)
	{
		if (current_time - sim->philos[i].last_meal_time >= sim->time_to_die)
		{
			// ¡Muerto!
			sim->simulation_should_end = 1; // Ponemos el flag
			pthread_mutex_unlock(&sim->sim_mutex);
			// ---- FIN SECCIÓN CRÍTICA ----

			// Imprimimos el mensaje de muerte (fuera del lock)
			print_status(&sim->philos[i], "died", 1);
			return (1); // 1 = Alguien murió
		}
		i++;
	}
	
	// Si nadie ha muerto y no todos han comido, liberamos el mutex
	pthread_mutex_unlock(&sim->sim_mutex);
	// ---- FIN SECCIÓN CRÍTICA ----
	
	return (0); // 0 = Nadie murió
}

/**
 * @brief La rutina del hilo monitor (el vigilante).
 *
 * Comprueba constantemente si la simulación debe terminar.
 */
void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;

	// Esperamos un poco antes de la primera comprobación
	// para dar tiempo a los filósofos a coger sus primeros tenedores.
	usleep(sim->time_to_die / 2 * 1000); 

	while (1)
	{
		// 1. Comprobamos muertes Y comidas en una sola función atómica
		if (check_death_and_meals(sim))
			break; // Si sí, salimos del bucle
		
		// Dormimos un poco para no quemar la CPU
		usleep(1000); // Chequeamos cada 1ms
	}
	return (NULL);
}