#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include <ThingSpeak.h>

// Definição dos pinos do sensor
#define trigPin 1
#define echoPin 16

// Definição dos parâmetros do ThingSpeak


// Definição dos parâmetros do WiFi
const char *rede = "LINKNET_JANETE _2.4G";
const char *senha = "jkgl0812";

WiFiClient wifiClient;

int distancia = 0;
String strDistancia = String(distancia);

// Definição dos pinos do LCD
LiquidCrystal lcd(14, 12, 13, 15, 2, 0);

void setup() {
  lcd.begin(16, 2); // Define a dimensão do LCD

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);

  fazerConexaoWifi();
}

void loop() {
  manterConexao();
  sensorRun();
  distancia = calcularDistancia();
  strDistancia = String(distancia);
  lcdRun();
  Serial.println(strDistancia + "cm");
  validarDados(distancia); 
}
void validarDados(int distancia){
  if(distancia != 0){
    enviarDados(strDistancia);
  }
}

void manterConexao() {
  // Verifica o estado da conexão WiFi
  if (WiFi.status() != WL_CONNECTED) {
    fazerConexaoWifi();
  }
}

void fazerConexaoWifi() {
  // Faz a conexão WiFi
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando......");
  
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

void lcdRun() {
  // Exibição da distância no LCD
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(distancia);
  lcd.print("cm");
}

void enviarDados(String strDistancia) {
  // Envio dos dados para o ThingSpeak
  delay(60000);
}
