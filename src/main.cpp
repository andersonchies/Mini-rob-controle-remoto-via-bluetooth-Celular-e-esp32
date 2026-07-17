#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial SerialBT;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Definições dos pinos Ponte H e I/Os
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define LED_PIN 2
#define ENA 13
#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
#define ENB 25
#define BUZZER 16
#define FAROL 17

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// configurações dos canais de PWM para controle da ponte
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define PWM_CHANNEL_A 0 // Canal PWM (0-15)
#define PWM_CHANNEL_B 1
#define PWM_FREQ 5000    // Frequência de 5kHz
#define PWM_RESOLUTION 8 // Resolução de 8 bits (0-255)

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Definições para a buzina
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#define PWM_BUZINA 2

bool flagbt;
char c;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// controles de velocidade dos motores
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int Max_Speed = 255;
int Low_Speed = 100;
int Off_Speed = 0;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Variável para alterar a música da buzina
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool changeSound = 0;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Definições das funções
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bool comando_recebido();
void Toca_Mario(void);
void nota(int freq, int duracao);
void harryPotter(void);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Setup do controlador
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void setup() {

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Configuração da Serial e do Bluetooth
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  Serial.println("Bluetooth Pronto");

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Configurações dos pinos
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(FAROL, OUTPUT);

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Configurações dos canais PWM
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  ledcSetup(PWM_CHANNEL_A, PWM_FREQ,
            PWM_RESOLUTION); // Configura canal A de PWM da ponte H Lado 1
  ledcSetup(PWM_CHANNEL_B, PWM_FREQ,
            PWM_RESOLUTION); // Configura canal A de PWM da ponte H Lado 1
  ledcAttachPin(ENA, PWM_CHANNEL_A); // Define pina ENA como PWM
  ledcAttachPin(ENB, PWM_CHANNEL_B); // Define pino ENB como PWM

  ledcSetup(PWM_BUZINA, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(BUZZER, PWM_BUZINA);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Código de loop
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void loop() {
  if (SerialBT.available()) {
    c = SerialBT.read();
    flagbt = true;
  }
  if (flagbt == true) {
    flagbt = comando_recebido();
  }
}

bool comando_recebido() {
  switch (c) {

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para avanço
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'F':
    Serial.println("Avanço");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_A, Max_Speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL_B, Max_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para recuo
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'B':
    Serial.println("Recuo");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, Max_Speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(PWM_CHANNEL_B, Max_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para virar para a esquerda
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'L':
    Serial.println("Esquerda");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_A, Max_Speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL_B, Off_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para virar para a direita
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'R':
    Serial.println("Direita");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_A, Off_Speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL_B, Max_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para andar para frente e para esquerda
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'G':
    Serial.println("Diagonal Esquerda");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_A, Low_Speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL_B, Max_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para andar para frente e para direita
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'H':
    Serial.println("Diagonal Direita");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_A, Max_Speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL_B, Low_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para andar para trás e para esquerda
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'I':
    Serial.println("Diagonal Esquerda Para Trás");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, Low_Speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(PWM_CHANNEL_B, Max_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para andar para trás e para direita
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'J':
    Serial.println("Diagonal Direita Para Trás");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, Max_Speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(PWM_CHANNEL_B, Low_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para parar o movimento
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'S':
    Serial.println("Stop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    ledcWrite(PWM_CHANNEL_A, Off_Speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    ledcWrite(PWM_CHANNEL_B, Off_Speed);
    break;

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Configura as saídas para ligar a buzina
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'Y':
    Serial.println("Buzina");
    if (changeSound == 0) {
      Toca_Mario();
    } else {
      harryPotter();
    }
    break;
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Liga e Desliga as Luzes
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  case 'X':
    Serial.println("Luzes Ligadas");
    digitalWrite(FAROL, HIGH);
    break;
  case 'x':
    Serial.println("Luzes Desligadas");
    digitalWrite(FAROL, LOW);
    break;
    return false;
  }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Função que toca a música do Mário
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void Toca_Mario(void) {
  nota(660, 100);
  nota(660, 100);
  delay(100);
  nota(660, 100);
  delay(100);
  nota(510, 100);
  nota(660, 100);
  delay(100);
  nota(770, 100);
  delay(300);
  nota(380, 100);
  delay(300);
}

void nota(int freq, int duracao) {
  if (freq == 0) {
    ledcWriteTone(PWM_BUZINA, 0);
  } else {
    ledcWriteTone(PWM_BUZINA, freq);
  }
  delay(duracao);
  ledcWriteTone(PWM_BUZINA, 0);
  delay(50); // pausa curta
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Função que toca a música do Harry Potter
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void harryPotter() {
  int tempo = 144;
  int wholenote = (60000 * 4) / tempo;

  int melody[] = {

      // Parte 1
      0,   2,  294, 4,  392, -4, 466, 8, 440, 4, 392, 2, 587, 4,  523, -2,
      440, -2, 392, -4, 466, 8,  440, 4, 349, 2, 415, 4, 294, -1, 294, 4,
  };

  int size = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < size; i += 2) {

    int freq = melody[i];
    int divider = melody[i + 1];
    int duration;

    if (divider > 0) {
      duration = wholenote / divider;
    } else {
      duration = (wholenote / abs(divider)) * 1.5;
    }

    if (freq == 0) {
      delay(duration);
    } else {
      nota(freq, duration * 0.9);
      delay(duration * 0.1);
    }
  }
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%
// MAPEAMENTO DE CHARS
// %%%%%%%%%%%%%%%%%%%%%%%%%%
// Frente F
// Trás B
// Esquerda L
// Direita R
// Frente esq G
// Frente dir H
// Trás esq I
// Trás dir J
// Buzina Y
// Liga Luzes X
// Desliga Luzes x
