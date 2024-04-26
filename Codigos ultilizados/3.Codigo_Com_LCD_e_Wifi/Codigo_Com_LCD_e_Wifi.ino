// C++ code
//
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

#define trigPin 1
#define echoPin 16

const char *rede = "LINKNET_JANETE _2.4G";
const char *senha = "jkgl0812";

float distancia = 0;

LiquidCrystal lcd(14, 12, 13, 15, 2, 0);

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  verificarConexao();
}

void verificarConexao() {
  WiFi.begin(rede, senha);
  while (WiFi.status() != WL_CONNECTED) //Aguarda a conexao
  {
    Serial.print("Estabelecendo conexão com ");
    Serial.println(WiFi.SSID()); //Imprime o nome da rede
    delay(500);
  }
  // Conectado
  Serial.print("Conectado a rede! Endereco IP ESP -> ");
  Serial.println(WiFi.localIP()); //Imprime o IP local do ESP
  lcd.setCursor(5, 0);
  lcd.print("Conectado");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1200);
}

void sensorRun() {
  /*Essa função ira fazer a ativação do sensor*/
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

float calcularDistancia() {
  /* Essa função é responsavel por fazer o calculo da
    distancia ou da quantidade de litros do reservatorio*/
  return (pulseIn(echoPin, HIGH) * 0.034 / 2);
}

void lcdRun() {
  /*Essa função é responsavel pela exibição dos calculos
    presentes presentes no metodo calcularDistancia()*/
  lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print((String)distancia + "cm");
}

void loop() {
  sensorRun();
  distancia = calcularDistancia();
  lcdRun();
  delay(800);
  Serial.println(String(distancia) + "cm");
}
