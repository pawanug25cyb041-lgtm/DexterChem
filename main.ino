#include <LiquidCrystal.h>

// Pin Definitions
const int tempPin = A0;   
const int waterPin = A1;  
const int buzzer = 8;     
const int relay = 9;      

// LCD Pin Setup (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  
  // Start with relay ON (Heater Running)
  digitalWrite(relay, HIGH); 
  
  lcd.begin(16, 2);
  lcd.print("SYSTEM READY");
  delay(1500);
}

void loop() {
  // Read Sensors
  int rawTemp = analogRead(tempPin);
  float tempC = (rawTemp * 5.0 / 1024.0) * 100.0; 
  int waterLevel = analogRead(waterPin);

  // Update Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(tempC); lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Water: "); lcd.print(waterLevel);

  // Safety Logic
  if (tempC > 90 || waterLevel < 200) {
    // UNSAFE: Shutdown and Alarm
    digitalWrite(relay, LOW);   
    
    // Pleasant Weep-Weep Sound
    tone(buzzer, 1000); 
    delay(300);
    tone(buzzer, 800);
    delay(300);
    
    lcd.clear();
    lcd.print("!! DANGER !!");
    lcd.setCursor(0, 1);
    lcd.print("AUTO SHUTDOWN");
  } else {
    // SAFE: System Normal
    digitalWrite(relay, HIGH); 
    noTone(buzzer);            
  }
  
  delay(200); 
}