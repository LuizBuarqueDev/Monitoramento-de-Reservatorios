#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include <PubSubClient.h>

// Definição dos pinos do sensor
#define trigPin 1
#define echoPin 16

// Definição dos parâmetros do WiFi
const char *rede = "LINKNET_JANETE _2.4G";
const char *senha = "jkgl0812";

// Definição dos parâmetros do MQTT
const char *mqtt_server = "35.199.93.123";
const int mqtt_port = 1883;
const char *mqtt_topic = "ifpe/esp-8266";

// Inicialização das variáveis
WiFiClient wifiClient;
PubSubClient client(wifiClient);

int distancia = 0;
int porcentagem = 0;
int litros = 0;

const int reservatorioFull = 35; // distancia quando o reservatorio está cheio
const int reservatorioEmpty = 63; // distancia quando o reservatorio está vazio

// Definição dos pinos do LCD
LiquidCrystal lcd(14, 12, 13, 15, 2, 0);

void setup() {
  // Configuração inicial do LCD e do serial
  lcd.begin(16, 2); // Define a dimensão do LCD
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);

  // Conectar ao WiFi
  fazerConexaoWifi();

  // Configuração do servidor MQTT
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
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
    enviarDados();
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

void fazerConexaoWifi() {
  // Faz a conexão WiFi
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando...");

  WiFi.begin(rede, senha);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando a ");
    Serial.println(WiFi.SSID());
    delay(5000);
  }

  // Conexão estabelecida
  Serial.print("Conectado à rede! Endereço IP do ESP -> ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Conectado");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1200);
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

void lcdRun() {
  // Exibição da distância no LCD
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(distancia);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print(porcentagem);
  lcd.print("%");
}

void enviarDados() {
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
