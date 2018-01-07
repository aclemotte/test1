# Firmware Engineer Test 1. INGENIA 

La solución se ha organizado de la siguiente manera, de manera a simular el sistema y sus entradas (sensor y memoria):

* Existen dos archivos que contienen los prototipos y las funciones que definen y utilizan la API: test1.c y test1.h
* Además, existen dos archivos que simulan la interrupción de un temporizador: timer.c y timer.h

## main()
El bloque principal de la simulación del sistema se encuentra en la función main() del archivo test1.c. La función main() realiza dos funciones para inicializar y finalizar el sistema: inicializacion() y finalizacion(). Entre estas dos funciones se realiza un bucle, implementado mediante la función ejecucionSistema(), hasta que se detecte un objeto. La detección de un objeto se indica mediante el valor de la variable global objetoDetectado.

## inicializacion()
Esta función invoca a las funciones de la API que inicializan la interfaz SPI, mediante SPIInit(), y el temporizador, mediante TimerInit(). La inicialización del temporizador incluye señalar la función que será ejecutada cuando se produzca el disparo, en nuestro caso, TimerISR(). Es importante inicializar primero el SPI ya que, en caso contrario, podríamos tener una interrupción del temporizador sin haber inicializado aún la interfaz SPI. La Además, inicializa el valor de objetoDetectado a cero. 

## finalizacion()
Esta función calcula el tiempo total de ejecución, mediante la función timetGetus(). 

## ejecucionSistema()
En este bucle se leen las tareas de la memoria, mediante la función leerMemoriaEeprom() y se ejecutan posteriormente mediante RobotTask(). La función leerMemoriaEeprom() ejecuta las funciones necesarias para leer el bus SPI: SPIEepromEnable(), SPIRead() y SPIEepromDisable(), y retorna el valor de la tarea a ser ejecutada por el robot. La función que ejecuta la tarea en el robot permite configurar la demora en la ejecución mediante la directiva ROBOTTASKTIMEMS, actualmente definida en 100ms. 

SPIRead() simula leer diferentes valores por cada llamada. Los valores retornados por esta función serán números consecutivos crecientes a partir del valor de SPIFIRSTREAD (defino en 124 actualmente). 

## TimerISR()
La función ejecucionSistema() es interrumpida por el temporizador, ya que el tiempo necesario para ejecutarse RobotTask() es de 100ms y el intervalo de interrupción es de 10ms.  Cuando el temporizador genera un interrupción se pasa a ejecutar la rutina de servicio de la interrupción TimerISR(). En TimerISR() se lee el valor del sensor óptico mediante la función leerSensor(), que al igual que la función leerMemoriaEeprom(), ejecuta las funciones necesarias para leer el bus SPI: SPISensorEnable(), SPIRead() y SPISensorDisable(), y retorna el valor del sensor óptico. El periodo de interrupción está establecido mediante la directiva SENSORUPDATEMS, actualmente declarada como 10 ms. 

En función de si el valor del sensor óptico, llamado valorSensor, es mayor o menor al umbral defino mediante SENSORTHRESHOLD (128 según documentación), se actualiza el valor de la variable global objetoDetectado, según la siguiente convención: objetoDetectado=1 si valorSensor>128, sino objetoDetectado=0 en el otro caso. ejecucionSistema() detiene su ejecución cuando objetoDetectado=1. Además de actualizar el valor de objetoDetectado, si valorSensor>128 se detiene el temporizador y el robot, mediante stop_timer(), y RobotStop() respectivamente. 

Aquí es importante notar que SPIRead() es invocada en el contexto de la lectura de la memoria y del sensor. Este es el motivo por el que se ha decido inicializar el valor de lecturaSPI en 124, un valor muy cercano al valor umbral 128. 

