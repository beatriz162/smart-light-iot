# Sistema Inteligente de Iluminação com ESP32 e MQTT

## Descrição

Este projeto apresenta um sistema inteligente de iluminação utilizando ESP32, sensor LDR e protocolo MQTT.

O sistema monitora automaticamente a luminosidade do ambiente por meio de um sensor LDR. Quando a luminosidade fica abaixo de um limite definido, o ESP32 aciona automaticamente um LED, simulando o funcionamento de uma luminária inteligente. Quando a luminosidade aumenta, o LED é desligado automaticamente.

Além do funcionamento automático, o sistema permite monitoramento e controle remoto em tempo real através do protocolo MQTT, possibilitando o acionamento manual da iluminação por meio de comandos enviados pelo MQTT Explorer.

## Componentes Utilizados

* ESP32
* Sensor LDR
* LED
* Resistores
* Jumpers
* Plataforma Wokwi
* MQTT Explorer
* Broker MQTT

## Funcionamento

O sensor LDR realiza a leitura contínua da luminosidade do ambiente.

Os dados são processados pelo ESP32, que decide automaticamente ligar ou desligar o LED conforme o nível de iluminação detectado.

O ESP32 publica informações em tempo real através dos seguintes tópicos MQTT:

* smartlight/luminosidade
* smartlight/status
* smartlight/modo

Além disso, o sistema recebe comandos pelo tópico:

* smartlight/comando

Comandos disponíveis:

* ON → Liga a lâmpada manualmente
* OFF → Desliga a lâmpada manualmente
* AUTO → Retorna o sistema para o modo automático

O MQTT Explorer é utilizado para monitorar as mensagens e enviar comandos ao sistema em tempo real.

## Protocolo MQTT

O protocolo MQTT foi utilizado para permitir uma comunicação leve e eficiente entre o ESP32 e o broker MQTT através da Internet.

Broker utilizado:

test.mosquitto.org

## Funcionalidades

* Monitoramento da luminosidade em tempo real
* Acionamento automático da iluminação
* Publicação do status da lâmpada
* Indicação do modo de operação (Automático ou Manual)
* Controle remoto via MQTT
* Simulação completa na plataforma Wokwi

## Autor

Projeto desenvolvido por Beatriz Pinheiro.

