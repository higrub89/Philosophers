
#include "../inc/philo.h"

int	main(void)
{
	t_sim	sim;
	t_philo	philo;

	// 1. Inicialización mínima
	// Usamos memset (permitida) para limpiar las estructuras
	memset(&sim, 0, sizeof(t_sim));
	memset(&philo, 0, sizeof(t_philo));
	
	// Obtenemos la hora de inicio
	sim.start_time = get_current_time();
	if (sim.start_time == 0)
		return (display_error("gettimeofday falló"), 1);

	// Asignamos valores de prueba
	sim.simulation_should_end = 0;
	philo.id = 1;      // Nuestro filósofo de prueba es el '1'
	philo.sim = &sim;  // Enlazamos el filósofo a la simulación

	// 2. Inicializamos los Mutexes (¡MUY IMPORTANTE!)
	if (pthread_mutex_init(&sim.write_mutex, NULL) != 0)
		return (display_error("fallo en mutex_init (write)"), 1);
	if (pthread_mutex_init(&sim.sim_mutex, NULL) != 0)
		return (display_error("fallo en mutex_init (sim)"), 1);

	// 3. ¡LA PRUEBA!
	
	// Mensaje de inicio
	print_status(&philo, "está probando el inicio");

	printf("--- Voy a dormir 2 segundos (2000 ms) ---\n");
	
	// Llamamos a precise_usleep
	precise_usleep(2000, &sim);
	
	printf("--- Acabo de despertar ---\n");

	// Mensaje de fin
	print_status(&philo, "está probando el fin");

	// 4. Limpieza
	pthread_mutex_destroy(&sim.write_mutex);
	pthread_mutex_destroy(&sim.sim_mutex);

	printf("--- Prueba completada con éxito ---\n");
	return (0);
}
