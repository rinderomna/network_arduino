# Laboratório Camada de Enlace
Repositório para o Laboratório Camada de Enlace, da disciplina "SSC0142 - Redes de Computadores" do ICMC - USP - São Carlos, ministrada pela professora Kalinka Regina Lucas Jaquie Castelo Branco.

## Grupo 6
Somos o grupo 6 (emissor / paridade ímpar) e pretendemos nos comunicar com o grupo 29 (receptor / paridade ímpar).
| **NUSP** | **Membro do Grupo 6**    |
|----------|--------------------------|
| 12543544 | Danielle Modesti         |
| 10310227 | Hélio Nogueira Cardoso   |
| 10691331 | Théo da Mota dos Santos  |


## Objetivo
Realizar uma comunicação síncrona entre duas plataformas _Arduino_.

## Requisitos
- O sistema deve manter comunicação síncrona entre as duas plataformas _Arduino_, ou seja, deve haver sincronização entre emissor e receptor por meio de um _clock_;
- O sistema deve implementar controle de erros em sua comunicação por meio da técnica de _bit_ de paridade;
- O sistema deve implementar um _handshake_ simples para a comunicação entre emissor e receptor.

### Detalhes do _Clock_
Para gerar o _clock_, será utilizado o esqueleto de função "Temporizador.h". Um temporizador (_timer_) é uma estrutura no microcontrolador que permite contagem de tempo a partir de um _clock_ interno ou externo.

O uso do temporizador é vantajoso porque o programa pode processar outras coisas e deixar o controle de _clock_ para o _background_. Outra vantagem é sua precisão, essencial para o sincronismo.

### _Handshake_
Forma de controle de fluxo, "acordo" entre emissor e receptor para que a transmissão possa ocorrer.
Dois sinais serão utilizados neste trabalho:
RTS (emissor -> receptor)
CTS (receptor -> emissor).

## Procedimento
Neste trabalho, o _Arduino_ emissor receberá um caractere pela sua porta serial, por meio do _Serial Monitor_ da plataforma, e deverá enviá-lo de forma serial e síncrona ao _Arduino_ receptor, o qual imprimirá os caracteres recebidos em sua porta serial, exibindo-os para o usuário por meio do _Serial Monitor_, de mesmo modo. Os caracteres a serem transmitidos devem pertencer à tabela de codificação _ASCII_ (https://upload.wikimedia.org/wikipedia/commons/d/dd/ASCII-Table.svg).

Na atividade, o _clock_ será configurado no arquivo "Temporizador.h". Para utilizar seus métodos disponíveis, incluiremos tal arquivo no programa principal.
