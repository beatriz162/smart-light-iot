#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos
const int ldrPin = 34;
const int ledPin = 2;

// Variáveis de controle
bool modoAutomatico = true;
bool estadoLampada = false;

// =========================
// RECEBE COMANDOS MQTT
// =========================
void callback(char* topic, byte* payload, unsigned int length) {

  String mensagem = "";

  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  Serial.println("================================");
  Serial.print("Comando recebido: ");
  Serial.println(mensagem);

  if (mensagem == "ON") {

    modoAutomatico = false;
    estadoLampada = true;

    Serial.println("Modo MANUAL");
    Serial.println("Lampada LIGADA");

  } 
  else if (mensagem == "OFF") {

    modoAutomatico = false;
    estadoLampada = false;

    Serial.println("Modo MANUAL");
    Serial.println("Lampada DESLIGADA");

  } 
  else if (mensagem == "AUTO") {

    modoAutomatico = true;

    Serial.println("Modo AUTOMATICO");
  }

  Serial.println("================================");
}

// =========================
// WIFI
// =========================
void setup_wifi() {

  Serial.println("Conectando ao WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
}

// =========================
// MQTT
// =========================
void reconnect() {

  while (!client.connected()) {

    Serial.println("Conectando ao MQTT...");

    String clientId = "SMARTLIGHT_";
    clientId += String(random(10000));

    if (client.connect(clientId.c_str())) {

      Serial.println("MQTT conectado!");

      client.subscribe("smartlight/comando");

      Serial.println("Inscrito em smartlight/comando");

    } else {

      Serial.print("Erro MQTT: ");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

// =========================
// SETUP
// =========================
void setup() {

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// =========================
// LOOP
// =========================
void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  int luminosidade = analogRead(ldrPin);

  // Modo automático
  if (modoAutomatico) {

    if (luminosidade < 2000) {
      estadoLampada = true;
    } else {
      estadoLampada = false;
    }
  }

  // Controle do LED
  if (estadoLampada) {

    digitalWrite(ledPin, HIGH);

    client.publish("smartlight/status", "ACESA");

  } else {

    digitalWrite(ledPin, LOW);

    client.publish("smartlight/status", "APAGADA");
  }

  // Publica luminosidade
  char msg[10];
  sprintf(msg, "%d", luminosidade);

  client.publish("smartlight/luminosidade", msg);

  // Publica modo
  if (modoAutomatico) {
    client.publish("smartlight/modo", "AUTO");
  } else {
    client.publish("smartlight/modo", "MANUAL");
  }

  Serial.println("-------------------------");
  Serial.print("Luminosidade: ");
  Serial.println(luminosidade);

  if (estadoLampada) {
    Serial.println("Status: ACESA");
  } else {
    Serial.println("Status: APAGADA");
  }

  delay(2000);
}
