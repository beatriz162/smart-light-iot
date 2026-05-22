#include <WiFi.h>
#include <PubSubClient.h>

// WIFI
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

// PINOS
const int ldrPin = 34;
const int ledPin = 2;

// WIFI
void setup_wifi() {

  Serial.println("Conectando WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
}

// MQTT
void reconnect() {

  while (!client.connected()) {

    Serial.println("Conectando MQTT...");

    if (client.connect("ESP32_BIAZINHA_2026")) {

      Serial.println("MQTT conectado!");

    } else {

      Serial.print("Erro MQTT: ");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

// SETUP
void setup() {

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
}

// LOOP
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  // LE SENSOR
  int luminosidade = analogRead(ldrPin);

  // CONVERTE
  char msg[10];

  sprintf(msg, "%d", luminosidade);

  // ENVIA MQTT
  client.publish("biazinha/luminosidade", msg);

  Serial.println("MQTT enviado!");
  Serial.print("Luminosidade: ");
  Serial.println(msg);

  // CONTROLE LED
  if (luminosidade < 2000) {

    digitalWrite(ledPin, HIGH);

    client.publish("biazinha/luz/status", "Ligada");

    Serial.println("LED LIGADO");

  } else {

    digitalWrite(ledPin, LOW);

    client.publish("biazinha/luz/status", "Desligada");

    Serial.println("LED DESLIGADO");
  }

  Serial.println("----------------");

  delay(2000);
}
