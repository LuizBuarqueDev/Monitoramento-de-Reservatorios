// C++ code
//
#include <ESP8266WiFi.h>
//#include <LiquidCrystal.h>

#define trigPin 1
#define echoPin 16

const char *rede = "LINKNET_JANETE _2.4G";
const char *senha = "Senha aqui";

float distancia = 0;
const float distanciaMax = 330;
const float distanciaMin = 15;

//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  //  lcd.begin(16, 2);
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
  Serial.print("Conectado a rede! Endereco IP ESP -> ");
  Serial.println(WiFi.localIP()); //Imprime o IP local do ESP
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
  /*lcd.clear();
    lcd.setCursor(6, 0);
    if ((distancia <= distanciaMax) && (distancia >= distanciaMin)) {
    lcd.print((String)distancia + "cm");
    } else {
    lcd.print("*******");
    }*/
}

void mapearLcd() {
  /*Essa função é responsavel pela exibição da barra
    presente no LCD*/
  /*lcd.setCursor(0, 1);
    for (int ln = 0; ln < map(distancia, distanciaMin, distanciaMax, 16, 0);ln++) lcd.print(char(255));
    {
    delay(20);
    }*/
}

void loop() {
  sensorRun();
  distancia = calcularDistancia();
  delay(500);
  //lcdRun();
  //mapearLcd();
  Serial.println(String(distancia) + "cm");
}
