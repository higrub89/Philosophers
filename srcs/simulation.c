/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* simulation.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/* localVarHTTP   +#+           */
/* Created: 2025/10/31 00:00:00 by ruben             #+#    #+#             */
/* Updated: 2025/10/31 00:00:00 by ruben            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief La rutina principal de un filósofo (lo que hace cada hilo).
 *
 * Esta es la función que se pasa a pthread_create.
 * Es un bucle de vida: comer, dormir, pensar.
 *
 * @param arg Un puntero void* a la estructura t_philo del filósofo.
 */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// Bucle de vida: se repite hasta que la simulación termine
	while (1)
	{
		// Comprobación de muerte (protegida)
		pthread_mutex_lock(&philo->sim->sim_mutex);
		if (philo->sim->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->sim->sim_mutex);
			break; // Salir del bucle si alguien murió
		}
		pthread_mutex_unlock(&philo->sim->sim_mutex);

		// (PRÓXIMO PASO: Aquí irán las acciones)
		// philo_eat(philo);
		// philo_sleep(philo);
		// philo_think(philo);

		// --- Test temporal ---
		print_status(philo, "está pensando (test)");
		usleep(500 * 1000); // Dormir 0.5 seg
	}
	return (NULL);
}

/**
 * @brief Lanza todos los hilos (filósofos y monitor).
 *
 * @param sim La estructura de simulación.
 * @return 1 si éxito, 0 si falla.
 */
int	start_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	// 1. Lanzar un hilo por cada filósofo
	while (i < sim->num_philos)
	{
		// pthread_create(puntero_al_hilo, atributos, funcion_a_ejecutar, datos)
		if (pthread_create(&sim->philos[i].thread, NULL,
				&philo_routine, &sim->philos[i]) != 0)
			return (display_error("Fallo al crear el hilo del filósofo"), 0);
		i++;
	}

	// 2. (PRÓXIMO PASO) Lanzar el hilo monitor
	//
	// pthread_t monitor_thread;
	// if (pthread_create(&monitor_thread, NULL, &monitor_routine, sim) != 0)
	//     return (display_error("Fallo al crear el hilo del monitor"), 0);
	

	// 3. Esperar a que todos los hilos de los filósofos terminen
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}

	// 4. (PRÓXIMO PASO) Esperar a que el monitor termine
	//
	// pthread_join(monitor_thread, NULL);
	
	return (1);
}