// C++ code
//
#include <ESP8266WiFi.h>
//#include <LiquidCrystal.h>

#define trigPin 1
#define echoPin 16

const int 

float distancia = 0;
const float distanciaMax = 330;
const float distanciaMin = 15;

//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 

void setup() {
//  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
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
