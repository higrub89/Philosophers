#include "../inc/philo.h"

// --- Colores para la salida ---
#define RESET   "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"

/**
 * @brief Función de ayuda para imprimir los argumentos que estamos probando.
 */
static void	print_test_case(int argc, char **argv)
{
	int	i;

	printf("Probando: ");
	i = 0;
	while (i < argc)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
}

/**
 * @brief Función de ayuda que ejecuta un solo caso de prueba.
 */
static void	run_test(int argc, char **argv)
{
	t_sim	sim;

	// Limpiamos la struct sim para cada prueba
	memset(&sim, 0, sizeof(t_sim));
	print_test_case(argc, argv);

	if (parse_args(&sim, argc, argv) == 1)
	{
		// parse_args devolvió 1 (éxito)
		printf("  -> " GREEN "PASS" RESET);
		printf(" (Filos: %d, T_Muerte: %ld, T_Comida: %ld, T_Sueño: %ld, Comidas: %d)\n",
			sim.num_philos, sim.time_to_die, sim.time_to_eat,
			sim.time_to_sleep, sim.num_meals_to_eat);
	}
	else
	{
		// parse_args devolvió 0 (fallo)
		printf("  -> " RED "FAIL (¡Esperado para argumentos malos!)\n" RESET);
	}
	printf("--------------------------------------------------\n");
}

/**
 * @brief Main principal para probar el parseo de argumentos.
 */
int	main(void)
{
	printf("--- Iniciando Pruebas de parse_args ---\n");

	// Test 1: Caso bueno (5 args)
	char	*good_5[] = {"./philo", "4", "800", "200", "200"};
	run_test(5, good_5);

	// Test 2: Caso bueno (6 args)
	char	*good_6[] = {"./philo", "5", "410", "200", "200", "7"};
	run_test(6, good_6);

	// --- PRUEBAS DE ARGUMENTOS MALOS ---

	// Test 3: Demasiado pocos argumentos
	char	*too_few[] = {"./philo", "4", "800", "200"};
	run_test(4, too_few);

	// Test 4: Demasiados argumentos
	char	*too_many[] = {"./philo", "1", "2", "3", "4", "5", "6"};
	run_test(7, too_many);

	// Test 5: Letra en medio (¡Tu caso!)
	char	*bad_char[] = {"./philo", "200", "125", "60", "60"};
	run_test(5, bad_char);

	// Test 6: Letra al principio
	char	*bad_char_2[] = {"./philo", "a5", "800", "200", "200"};
	run_test(5, bad_char_2);

	// Test 7: Solo un signo
	char	*bad_sign[] = {"./philo", "200", "125", "60", "60"};
	run_test(5, bad_sign);

	// Test 8: Rango 0 (no permitido)
	char	*zero_philo[] = {"./philo", "0", "800", "200", "200"};
	run_test(5, zero_philo);

	// Test 9: Rango negativo (no permitido)
	char	*neg_time[] = {"./philo", "4", "-800", "200", "200"};
	run_test(5, neg_time);

	// Test 10: Rango negativo en comidas (no permitido)
	char	*neg_meals[] = {"./philo", "4", "800", "200", "200", "-5"};
	run_test(6, neg_meals);

	printf("--- Pruebas de parse_args completadas ---\n");
	return (0);
}