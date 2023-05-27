#include "Temporizador.h"

#define PINO_TX 13 // Emissor envia dados por esse pino
#define PINO_RTS_OUT 8 // O emissor seta o RTS
#define PINO_CTS_IN 9 // O receptor seta o CTS
#define BAUD_RATE 1
#define HALF_BAUD 1000/(2*BAUD_RATE)

// Ultimo caractere lido do Serial Monitor para ser transmitido via USB
char c;

// Indice do bit do quadro que esta sendo montado
int curr_bit = 0;

// Um quadro tem 11 bits: 1 start bit, 8 bits de dado, 1 bit de paridade e 1 end bit
bool frame[11];

// Disposicao a se comunicar (RTS + CTS)
bool handshake = false;

// Controle logico da transmissao
bool transmitting = false;

// Pedido para estabelecer comunicacao com receptor
bool RTS = false;

// Confirmacao de estabelecimento de comunicacao
bool CTS = false;

// Calcula bit de paridade - Par ou impar
bool bitParidade(char dado){
    int asciiValue = (int)dado;  // Converter char para valor ASCII
    int countOnes = 0;

    while (asciiValue > 0) {
        countOnes += (asciiValue % 2);  // Checar o LSB
        asciiValue >>= 1;  // Right shift de 1 para obter proximo bit
    }

    return countOnes % 2 == 0;
}

void make_frame(char c, bool frame[]) {
    // SB = 0
    frame[0] = false;
    
    int asciiValue = (int)c;
    
    // LSB --> MSB
    for (int i = 8; i > 0; i--) {
      frame[i] = (asciiValue % 2 == 1);
      asciiValue >>= 1;
    } 
    
    frame[9] = bitParidade(c);

    // EB = 1
    frame[10] = true;
}

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou? 
// Interromper execucao do loop do arduino para realizar transmissao
ISR(TIMER1_COMPA_vect) {
  digitalWrite(PINO_TX, frame[curr_bit] ? HIGH : LOW);
  Serial.write(frame[curr_bit] ? '1' : '0');

  // Ultimo bit foi transmitido
  if (curr_bit == 10) {
    // Fim da conexao
    handshake = false;
    RTS = false;
    digitalWrite(PINO_RTS_OUT, LOW);

    // Acabou a transmissao de dados
    transmitting = false;
    paraTemporizador();

    curr_bit = 0;
  } else {
    // Passa para o proximo bit
    curr_bit++; 
  }
}

// Executada uma vez quando o Arduino reseta
void setup() {
  // Desabilita interrupcoes
  noInterrupts();

  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(9600);

  // Inicializa TX
  pinMode(PINO_TX, OUTPUT);
  pinMode(PINO_RTS_OUT, OUTPUT);
  digitalWrite(PINO_RTS_OUT, LOW);
  pinMode(PINO_CTS_IN, INPUT);

  // Configura timer - clock
  configuraTemporizador(BAUD_RATE);

  // Habilita interrupcoes
  interrupts();
}

// O loop() eh executado continuamente (como um while(true))
void loop() {
  // Ha dados para transmitir
  if (!transmitting && Serial.available() > 0) {
    char caractere = Serial.read();

    c = caractere;
    transmitting = true;
    make_frame(c, frame);

    // Imprimindo o que vamos transmitir
    Serial.print("Deseja-se transmitir: ");
    for (int i = 0; i <= 10; i++) {
      Serial.print(frame[i] ? "1" : "0");
    }
    Serial.print("\n");
    Serial.print("Transmitindo: ");

    // Solicitando conexao
    digitalWrite(PINO_RTS_OUT, HIGH);
    RTS = true;
  }

  // Verifica se receptor esta pronto para receber dados
  CTS = digitalRead(PINO_CTS_IN);

  // Mudanca no status de handshake para verdadeiro
  if (!handshake && (RTS && CTS)) {
    // Start no clock
    iniciaTemporizador();
    handshake = true;
  }
}