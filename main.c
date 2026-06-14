/**
 * @file    main.c
 * @brief   Punto de entrada del sistema de control de LEDs por potenciometros.
 *
 * =============================================================================
 * CONCLUSION DEL EQUIPO
 * Integrantes: Pablo Mansilla Hernández
 *
 * Realizando este codigo comprendi como es que, con el uso pvParameters junto con task_params_t, se
 * puede instanciar una sola función de tarea varias veces con configuraciones distintas, evitando
 * que se necesite duplicar partes del codigo
 * 
 * 
 * ¿Qué sucedería si los bloques task_params_t se declararan como variables locales en tasks_create_all() 
 * en lugar de static? ¿Cómo lo detectarías experimentalmente?
 * R= Cuando una función del codigo termina, todas sus variables locales desaparecen de la memoria.
 * Si los parámetros no son static, al retornar tasks_create_all() los tres bloques de parámetros se borran,
 * pero las tareas siguen corriendo e intentando leer esos datos los cuales ya no existen.
 * Experimentalmente se verian valores absurdos en la terminal, el sistema reiniciándose solo por watchdog,
 * o nombres de canal corruptos en los mensajes.
 * 
 * 
 * =============================================================================
 *
 * Descripcion:
 *   Inicializa los perifericos (ADC y LEDC) y arranca tres tareas FreeRTOS.
 *   Cada tarea lee un potenciometro y ajusta el brillo del LED correspondiente.
 *
 *   La logica de negocio esta completamente encapsulada en los modulos:
 *     - adc_reader : lectura de potenciometros via ADC oneshot
 *     - leds       : control de brillo via LEDC (PWM)
 *     - tasks      : tareas FreeRTOS y sus parametros
 *
 * Plataforma : ESP32 / ESP-IDF 5.x - 6.x  / FreeRTOS
 * IDE        : VS Code + PlatformIO (framework: espidf)
 * Estandar   : C99
 */

#include "adc_reader.h"
#include "leds.h"
#include "tasks.h"

/* ------------------------------------------------------------------ */
/*  Punto de entrada                                                   */
/* ------------------------------------------------------------------ */

void app_main(void)
{
    /* TODO 1. Inicializar subsistema ADC (tres potenciometros) */
    adc_reader_init();
    /* TODO 2. Inicializar subsistema LED PWM (tres canales LEDC) */
    leds_init();
    /* TODO 3. Crear las tres tareas FreeRTOS e iniciar el scheduler */
    tasks_create_all();
    /* app_main retorna; FreeRTOS continua ejecutando las tareas */
}