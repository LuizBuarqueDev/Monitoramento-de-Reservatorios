#include <LiquidCrystal.h>

// Definição dos pinos do LCD
LiquidCrystal lcd(14, 12, 13, 15, 2, 0);

void lcdSetup() {
  lcd.begin(16, 2); // Define a dimensão do LCD
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
