#define PINO_TX 13
#define PINO_RTS_OUT 8
#define PINO_CTS_IN 9
#define BAUD_RATE 1
#define HALF_BAUD 1000/(2*BAUD_RATE)

#include "Temporizador.h"

char c;
int curr_bit = 0;
bool frame[11];
bool handshake = false;
bool transmitting = false;
bool RTS = false;
bool CTS = false;

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

void make_frame(char c, bool frame[]) {
    frame[0] = true;
    
    int asciiValue = (int)c;
    
    for (int i = 8; i > 0; i--) {
      frame[0] = true;
      frame[i] = (asciiValue % 2 == 1);
      asciiValue >>= 1;
    }
    
    frame[9] = bitParidade(c);
    frame[10] = true;
}

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou?
ISR(TIMER1_COMPA_vect){
  digitalWrite(PINO_TX, frame[curr_bit] ? HIGH : LOW);
  Serial.write(frame[curr_bit] ? '1' : '0');

  if (curr_bit == 10) {
    RTS = false;
    handshake = false;
    transmitting = false;
    paraTemporizador();
    digitalWrite(PINO_RTS_OUT, HIGH);

    curr_bit = 0;
  } else {
    curr_bit++;
  }
}

// Executada uma vez quando o Arduino reseta
void setup(){
  //desabilita interrupcoes
  noInterrupts();
  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);
  // Inicializa TX ou RX
  pinMode(PINO_TX, OUTPUT);
  pinMode(PINO_RTS_OUT, OUTPUT);
  pinMode(PINO_CTS_IN, INPUT);
  // Configura timer
  configuraTemporizador(BAUD_RATE);
  // habilita interrupcoes
  interrupts();
}

// O loop() eh executado continuamente (como um while(true))
void loop( ) {
  if (!transmitting && Serial.available() > 0) {
    char caractere = Serial.read();

    if (caractere != '\n') {
      c = caractere;
      transmitting = true;
      make_frame(c, frame);

      for (int i = 0; i <= 10; i++) {
        Serial.print(frame[i] ? "1" : "0");
      }
      Serial.print("\n");

      digitalWrite(PINO_RTS_OUT, HIGH);
  
      RTS = true;
    } 
  }

  CTS = digitalRead(PINO_CTS_IN);

  if (!handshake && (RTS && CTS)) {
    handshake = true;

    iniciaTemporizador();
    transmitting = true;
  }
}