
uint8_t objetoDetectado;







///Funciones principales


void inicializacion(void);

void ejecucionSistema(void);

void finalizacion(void);






///Funciones secundarias


uint8_t leerMemoriaEeprom();






///Funciones API

///ROBOT


void RobotTask(uint8_t u8Command);





///TIMER


void TimerInit(void);

//Interrupt void TimerISR(void);
void TimerISR(void);

uint32_t TimetGetus(void);






///SPI


void SPIInit(void);

void SPIEepromEnable(void);

void SPIEepromDisable(void);

uint8_t SPIRead(void);
