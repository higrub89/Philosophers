#include "../inc/philo.h"

/**
 * @brief Libera toda la memoria y destruye todos los mutexes.
 *
 * Es la función de limpieza que se llama al final,
 * tanto si la simulación ha ido bien como si ha fallado
 * después de la inicialización.
 */
static void	cleanup(t_sim *sim)
{
	int	i;

	if (!sim) // Seguridad extra
		return;
	
	// 1. Destruir todos los mutexes de los tenedores
	i = 0;
	while (i < sim->num_philos && sim->forks)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	// 2. Destruir los mutexes de control
	pthread_mutex_destroy(&sim->write_mutex);
	pthread_mutex_destroy(&sim->sim_mutex);
	
	// 3. Liberar toda la memoria (malloc)
	if (sim->philos)
		free(sim->philos);
	if (sim->forks)
		free(sim->forks);
}

/**
 * @brief Punto de entrada principal del programa.
 */
int	main(int argc, char **argv)
{
	t_sim	sim; // Nuestra estructura principal que lo contiene todo

	// 0. Inicializar la estructura a cero para evitar basura
	memset(&sim, 0, sizeof(t_sim));

	// 1. Parsear y validar los argumentos
	if (!parse_args(&sim, argc, argv))
		return (1); // El error ya se ha impreso en parse_args

	// 2. Inicializar la simulación (mallocs y mutexes)
	if (!init_simulation(&sim))
	{
		// Si init falla, cleanup se encarga de liberar
		// lo que se haya podido reservar a medias.
		cleanup(&sim);
		return (1);
	}
	
	// 3. (PRÓXIMO PASO) Lanzar la simulación (crear hilos)
	//
	if (!start_simulation(&sim))
	{
	     cleanup(&sim);
	     return (1);
	}
	printf("-----Simulación Terminada-----\n");
	// 4. Limpiar todos los recursos
	cleanup(&sim);
	
	return (0);
}
