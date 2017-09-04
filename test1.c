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
}

void finalizacion()
{
	printf("finalizacion\n");
}






///Funciones API

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




///SPI


void SPIInit(void)
{
	//tiempo 7 ms
	Sleep(7);
	printf("\tSPIInit\n");
}
