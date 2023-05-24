# Laboratório Camada de Enlace
Repositório para o Laboratório Camada de Enlace, da disciplina "SSC0142 - Redes de Computadores" do ICMC - USP - São Carlos, ministrada pela professora Kalinka Regina Lucas Jaquie Castelo Branco.

## Objetivo
Realizar uma comunicação síncrona entre duas plataformas Arduino.

## Requisitos
- O sistema deve manter comunicação síncrona entre as duas plataformas Arduino, ou seja, deve haver sincronização entre emissor e receptor por meio de um clock;
- O sistema deve implementar controle de erros em sua comunicação por meio da técnica de bit de paridade;
- O sistema deve implementar um handshake simples para a comunicação entre emissor e receptor.

### Detalhes do Clock
To be written.

## Procedimento
Neste trabalho, o Arduino emissor receberá um caractere pela sua porta serial, por meio do Serial Monitor da plataforma, e deverá enviá-lo de forma serial e síncrona ao Arduino receptor, o qual imprimirá os caracteres recebidos em sua porta serial, exibindo-os para o usuário por meio do Serial Monitor, de mesmo modo. Os caracteres a serem transmitidos devem pertencer à tabela de codificação ASCII.
