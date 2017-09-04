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
}

void ejecucionSistema()
{
	printf("ejecucionSistema\n");
}

void finalizacion()
{
	printf("finalizacion\n");
}
