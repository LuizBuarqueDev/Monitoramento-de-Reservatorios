// Definição dos parâmetros do WiFi
const char *rede = "LINKNET_JANETE _2.4G";
const char *senha = "jkgl0812";

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
