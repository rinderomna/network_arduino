#define PINO_RX 13
#define PINO_TX 13
#define BAUD_RATE 1
#define HALF_BAUD 1000/(2*BAUD_RATE)

#include "Temporizador.h"

// Calcula bit de paridade - Par ou impar
bool bitParidade(char dado){
    int asciiValue = (int)dado;  // Convert char to ASCII value
    int countOnes = 0;

    while (asciiValue > 0) {
        countOnes += (asciiValue % 2);  // Check the least significant bit
        asciiValue >>= 1;  // Right shift by 1 to get the next bit
    }

    return countOnes % 2 == 0;
}

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou?
ISR(TIMER1_COMPA_vect){
  //>>>> Codigo Aqui <<<<
}

// Executada uma vez quando o Arduino reseta
void setup(){
  //desabilita interrupcoes
  noInterrupts();
  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);
  // Inicializa TX ou RX
  //>>>> Codigo Aqui <<<<
  // Configura timer
  //>>>> Codigo Aqui <<<<
  // habilita interrupcoes
  interrupts();
}

// O loop() eh executado continuamente (como um while(true))
void loop ( ) {
  //>>>> Codigo Aqui <<<<
}
