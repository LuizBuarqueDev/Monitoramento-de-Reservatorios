// C++ code
//
#define trigPin 1
#define echoPin 2
#define ledPin 13

float distancia = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorRun();
  distancia = calcularDistancia();
  //piscarLed();
  delay(800);
  Serial.println(String(distancia) + "cm");
  
}
void piscarLed() {
  digitalWrite(ledPin, HIGH);
  delay(5000);
  digitalWrite(ledPin, LOW);
  delay(300);
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
