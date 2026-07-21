# 🚗 Mini Robô com ESP32 via Bluetooth

Projeto de um carrinho controlado por celular usando ESP32 e Bluetooth.

## ⚙️ Projeto
- Toda a programação foi realizada com o PlatformIO
- Para encontrar o código no github vá na pasta src, o código é o arquivo main.cpp
- Para editar no ArduinoIDE, é necessário criar um novo projeto, copiar o código do arquivo main.cpp, e remover o seguinte trecho "#include <Arduino.h>", e instalar as bibliotecas necessárias.

## 📡 Tecnologias
- ESP32
- Bluetooth Serial
- ESP32 / PlatformIO

## 🎮 Controle
Comandos recebidos via app Bluetooth:

| Comando | Ação |
|--------|------|
| F | Frente |
| B | Ré |
| L | Esquerda |
| R | Direita |
| G | Frente Esquerda |
| H | Frente Direita |
| I | Trás Esquerda |
| J | Trás Direita |
| Y | Buzina |
| X | Liga Farol |
| x | Desliga Farol |

## 🔊 Extras
- Buzina tocando música do Mario 🍄

## ⚙️ Como usar
1. Conectar no Bluetooth: `ESP32_BT`
2. Usar app de controle Arduino Bluetooth Control, controle de carro
3. Enviar comandos
