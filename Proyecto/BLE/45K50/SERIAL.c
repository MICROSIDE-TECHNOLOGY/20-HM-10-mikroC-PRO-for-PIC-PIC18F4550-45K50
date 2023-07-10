/*******************************************************************************
Company:
Microside Technology Inc.

File Name:
Bluethooth2.mcppi

Product Revision  :  1
Device            :  X-TRAINER
Driver Version    :  1.0
********************************************************************************/

/*******************************************************************************
Para usar el c�digo con bootloader, configurar como lo indica MICROSIDE:
1) Tools> Options> Output> Output Settings> Marcar "Long HEX format"
2) Project> Edit Project> Insertar 48.000000 en "MCU Clock Frequency [MHz]" box
********************************************************************************/

#pragma orgall 0x1FFF                //Espacio reservado para bootloader
#define LED_ON       LATA4_bit = 1   //Se declara una definici�n donde se asigna el pin de salida y el estado l�gico
#define LED_OFF      LATA4_bit = 0   //Se declara una definici�n donde se asigna el pin de salida y el estado l�gico
#define BOTON PORTA.f2               //Se declara una definici�n que contine la funcion que determian el estado de una entrada digital

void main() org 0x2000               //Se define el registro a partir del cual se almacenara el codigo l�gico
{
  ANSELC = 0;
  TRISB = 0x00;                      //Puerto B como salida
  LATA4_bit = 0;                     //Pin A4 en estado bajo
  TRISA4_bit = 0;                    //Pin A4 como salida
  TRISA2_bit = 1;                    //Pin A2 como salida
  ANSA2_bit = 0;                     //Pin A2 como digital
  UART1_Init(9600);                  //Se asigna la velocidad del baudrate
  while(1){
    if (UART1_Data_Ready() == 1) {   //Pregunta si ha recibido alg�n dato por el puerto serial

      char Caracter = UART1_Read();  //Guarda el caracter

      if (Caracter == '0') {
        LED_OFF;                     //Apaga el LED
        UART1_Write_Text("LED APAGADO");
      }
      else if (Caracter == '1') {
        LED_ON;                      //Enciende el LED
        UART1_Write_Text("LED ENCENDIDO");
      }
      else if (Caracter == '?') {
        if (BOTON==1) {              //Pregunta el estado del bot�n
          UART1_Write('0');          //Env�a un 0 si el bot�n no est� presionado
        } else {
          UART1_Write('1');          //Env�a un 1 si el bot�n est� presionado
        }
      }
    }
  }
}