# Sistema Inteligente de Iluminação com ESP32 e MQTT

## Descrição

Este projeto apresenta um sistema inteligente de iluminação residencial utilizando ESP32, sensor LDR e protocolo MQTT.

O sistema monitora automaticamente a luminosidade do ambiente através de um sensor LDR. Quando o ambiente apresenta baixa luminosidade, o ESP32 aciona um LED automaticamente.

As informações de luminosidade e estado do LED são transmitidas via protocolo MQTT utilizando conexão TCP/IP através da internet.

## Componentes Utilizados

- ESP32
- Sensor LDR
- LED
- Resistores
- Jumpers
- Plataforma Wokwi
- MQTT Explorer
- Broker MQTT Mosquitto

## Funcionamento

O sensor LDR realiza a leitura da luminosidade do ambiente.

Os dados são processados pelo ESP32, que toma a decisão de ligar ou desligar o LED automaticamente.

Os dados também são enviados para um broker MQTT utilizando os tópicos:

- biazinha/luminosidade
- biazinha/luz/status

O MQTT Explorer é utilizado para monitorar as mensagens em tempo real.

## Protocolo MQTT

O protocolo MQTT foi utilizado para permitir comunicação leve e eficiente entre o dispositivo ESP32 e o broker MQTT através da internet.

O broker utilizado foi:

test.mosquitto.org

## Autor

Projeto desenvolvido por Beatriz Pinheiro
