/*
 ============================================================================
 Author      : aclemotte
 Description : Firmware Engineer Test 1. INGENIA
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "test1.h"
#include "timer.h"



#define SENSORUPDATEMS 10
#define ROBOTTASKTIMEMS 100
#define SPIFIRSTREAD 124





int main(void) {

	inicializacion();//12ms
	ejecucionSistema();
	finalizacion();
	return EXIT_SUCCESS;
}



///Funciones principales


//5ms+7ms=12ms
void inicializacion()
{
	printf("inicializacion\n");
	objetoDetectado = 0;
	SPIInit();//7ms
	TimerInit();//5ms
}

void ejecucionSistema()
{
	printf("ejecucionSistema\n");
	while(!objetoDetectado)
	{
		uint8_t tarea = leerMemoriaEeprom();//7us
		RobotTask(tarea);//100ms. Si esta funcion es interrumpida y es necesario pararla, la ISR la detendrá.
	}
}

void finalizacion()
{
	printf("finalizacion\n");
	uint32_t usExe = TimetGetus();
	printf("Han pasado %dus desde la inicialización del temporizador\n", usExe);
}






///Funciones secundarias


//1us+5us+1us=7us
uint8_t leerMemoriaEeprom()
{
	printf("leerMemoriaEeprom\n");
	SPIEepromEnable();//1us
	uint8_t tarea = SPIRead();//5us
	SPIEepromDisable();//1us
	return tarea;
}






///Funciones API

///ROBOT


void RobotTask(uint8_t u8Command)
{
	//tiempo 100 ms
	printf("RobotTask (start): %d\n", u8Command);
	Sleep(ROBOTTASKTIMEMS);
	printf("RobotTask (end): %d\n", u8Command);
}

///TIMER

void TimerInit(void)
{
	//tiempo 5 ms
	Sleep(5);
	start_timer(SENSORUPDATEMS, &TimerISR);
	printf("\tTimerInit\n");
}

//Interrupt void TimerISR(void) --> simulado por
void TimerISR(void)
{
}

uint32_t TimetGetus(void)
{
	uint32_t usNumber = 10;
	printf("TimetGetus: %d\n", usNumber);
	return usNumber;
}






///SPI


void SPIInit(void)
{
	//tiempo 7 ms
	Sleep(7);
	printf("\tSPIInit\n");
}

void SPIEepromEnable(void)
{
	//tiempo 1us
	printf("\tSPIEepromEnable\n");
}

void SPIEepromDisable(void)
{
	//tiempo 1us
	printf("\tSPIEepromDisable\n");
}

//simula leer diferentes valores por cada llamada
uint8_t SPIRead(void)
{
	//tiempo 5 us
	static uint8_t lecturaSPI = SPIFIRSTREAD;
	lecturaSPI++;
	printf("\tSPIRead %d\n", lecturaSPI);
	return lecturaSPI;
}
