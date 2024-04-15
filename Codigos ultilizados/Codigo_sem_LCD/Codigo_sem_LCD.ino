// C++ code
//

#define trigPin 1
#define echoPin 16

float distancia = 0;
const float distanciaMax = 330;
const float distanciaMin = 15;

void setup() {
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

void loop() {
  sensorRun();
  distancia = calcularDistancia();
  delay(500);
  Serial.println(String(distancia) + "cm");
}
