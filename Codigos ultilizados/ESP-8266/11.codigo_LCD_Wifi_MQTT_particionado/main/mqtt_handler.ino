#include <PubSubClient.h>

// Definição dos parâmetros do MQTT
extern const char *mqtt_server;
extern const int mqtt_port;
extern const char *mqtt_topic;

// Variável global do cliente MQTT (definida no main.ino)
extern WiFiClient wifiClient;
extern PubSubClient client;

void setupMQTT() {
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
}

void enviarDados(int distancia, int porcentagem, int litros) {
  // Envio dos dados via MQTT em formato JSON
  char msg[100];
  sprintf(msg, "{\"distancia\": %d, \"porcentagem\": %d, \"litros\": %d}", distancia, porcentagem, litros);
  client.publish(mqtt_topic, msg);
  Serial.println("Enviando dados: " + String(msg));
  delay(60000);
}

void reconnect() {
  // Reconectar ao servidor MQTT
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}
