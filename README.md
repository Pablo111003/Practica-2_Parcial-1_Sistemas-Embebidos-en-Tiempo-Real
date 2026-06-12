# Nombres: Pablo Mansilla Hernández (9129)

# Descripción del Codigo:

Este codigo consiste en un sistema multitarea utilizando FreeRTOS, donde se lee de forma simultanea tres potenciometros mediante los ADCs que tiene la ESP32, controlando el brillo de
tres LEDs con PWM. La intensidad de cada uno de los LEDs, es proporcional al valor de su potenciometro correspondiente


# Tabla de pines:

GPIO 36 (VP) -> Potenciometro 1 -> LED 1 -> Resistencia -> GND

GPIO 39 (VN) -> Potenciometro 2 -> LED 2 -> Resistencia -> GND

GPIO 34 -> Potenciometro 3 -> LED 3 -> Resistencia -> GND


# Conclusiones:

Realizando este codigo comprendi como es que, con el uso pvParameters junto con task_params_t, se puede instanciar una sola función de tarea varias veces con configuraciones distintas,
evitando que se necesite duplicar partes del codigo


# Preguntas:

1. ¿Qué sucedería si los bloques task_params_t se declararan como variables locales en tasks_create_all() en lugar de static? ¿Cómo lo detectarías experimentalmente?
   R= Cuando una función del codigo termina, todas sus variables locales desaparecen de la memoria. Si los parámetros no son static, al retornar tasks_create_all()
   los tres bloques de parámetros se borran, pero las tareas siguen corriendo e intentando leer esos datos los cuales ya no existen.
   Experimentalmente se verian valores absurdos en la terminal, el sistema reiniciándose solo por watchdog, o nombres de canal corruptos en los mensajes.

2. Las tres tareas tienen el mismo periodo (50 ms) pero prioridades distintas. ¿En qué situación se hace visible la diferencia de prioridad en la salida del terminal?
   R= Si cada tarea trabaja por si sola, entonces no se nota, pero si dos o más tareas terminan su vTaskDelay exactamente al mismo tiempo, el planificador tiene que elegir cuál corre
   primero, eligiendo siempre la tarea de mayor prioridad.

3. ¿Por qué se usa vTaskDelay(pdMS_TO_TICKS(50)) en lugar de un for con retardo de software? ¿Qué diferencia implica para el planificador?
   R= Cuando se utiliza un bucle "for", el procesador cuente números sin hacer nada útil, pero sin soltar el CPU, esto provoca que las otras tareas no puedan ejecutarse mientras tanto,
   "vTaskDelay" en cambio, hace que la tarea se bloquee durante 50 ms, dejando asi que el procesador pueda atender a las demas tareas



