
uint8_t objetoDetectado;







///Funciones principales


void inicializacion(void);

void ejecucionSistema(void);

void finalizacion(void);











///Funciones API




///TIMER


void TimerInit(void);

//Interrupt void TimerISR(void);
void TimerISR(void);

uint32_t TimetGetus(void);






///SPI


void SPIInit(void);

