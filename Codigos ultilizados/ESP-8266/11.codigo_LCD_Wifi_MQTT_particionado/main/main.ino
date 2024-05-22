#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include <PubSubClient.h>

// Definição dos pinos do sensor
#define trigPin 1
#define echoPin 16

// Inicialização das variáveis
int distancia = 0;
int porcentagem = 0;
int litros = 0;

const int reservatorioFull = 35; // distancia quando o reservatorio está cheio
const int reservatorioEmpty = 63; // distancia quando o reservatorio está vazio

// Variável do cliente MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  // Configuração inicial do LCD e do serial
  lcdSetup();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);

  // Conectar ao WiFi
  fazerConexaoWifi();

  // Configuração do servidor MQTT
  setupMQTT();
}

void loop() {
  // Manter conexão WiFi e MQTT
  manterConexao();

  // Executar sensor e calcular distância e porcentagem
  sensorRun();
  distancia = calcularDistancia();
  porcentagem = calcularPorcentagem();

  // Atualizar display LCD e enviar dados
  lcdRun();
  Serial.println(String(distancia) + "cm");
  validarDados(distancia);  
}

void validarDados(int distancia) {
  if (distancia != 0) {
    enviarDados(distancia, porcentagem, litros);
  }
}

void manterConexao() {
  // Verifica o estado da conexão WiFi
  if (WiFi.status() != WL_CONNECTED) {
    fazerConexaoWifi();
  }

  // Verifica o estado da conexão MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void sensorRun() {
  // Ativação do sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

int calcularDistancia() {
  // Cálculo da distância
  return (pulseIn(echoPin, HIGH) * 0.034 / 2);
}

int calcularPorcentagem() {
  int distanciaRestante = distancia - reservatorioFull;
  int distanciaTotal = reservatorioEmpty - reservatorioFull;

  if (distanciaRestante < 0) {
    // O reservatório está completamente cheio
    return 100;
  } else if (distanciaRestante >= distanciaTotal) {
    // O reservatório está completamente vazio
    return 0;
  } else {
    // Calcula a porcentagem com base na distância restante
    return 100 - ((distanciaRestante * 100) / distanciaTotal);
  }
}
