// Include the LCD library
#include <LiquidCrystal.h>

// Initialize the LCD with the appropriate pins
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Define pins for fan and pump
const int Fan_Pin = 6;
const int Pump_Pin = 7;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print(" IoT SMART FARMING ");

  // Define output pins
  pinMode(Fan_Pin, OUTPUT);
  pinMode(Pump_Pin, OUTPUT);

  // Define input pins
  pinMode(A1, INPUT); // Rain sensor
}

void loop() {
  // ----------------------------
  // 1. Temperature Sensing
  int tempReading = analogRead(A0);  // Read analog value from LM35
  float mV = (tempReading / 1023.0) * 5000; // Convert to millivolts
  int Temp = mV / 10;  // Convert to Celsius
  lcd.setCursor(0, 1);
  lcd.print(" T=");
  lcd.print(Temp);
  lcd.print("'C  ");

  // ----------------------------
  // 2. Rain Detection
  int rain = digitalRead(A1);
  if (rain == 0) {
    lcd.setCursor(10, 1);
    lcd.print(" R=NO ");
  } else {
    lcd.setCursor(10, 1);
    lcd.print(" R=YES");
  }

  // ----------------------------
  // 3. Soil Moisture Sensing
  int soilReading = analogRead(A2);
  int soilMoisture = soilReading / 10;  // Convert to percentage
  lcd.setCursor(0, 2);
  lcd.print(" S=");
  lcd.print(soilMoisture);
  lcd.print("%  ");

  // ----------------------------
  // 4. Humidity Sensing
  int humidityReading = analogRead(A3);
  int humidity = humidityReading / 10;  // Convert to percentage
  lcd.setCursor(10, 2);
  lcd.print(" H=");
  lcd.print(humidity);
  lcd.print("%  ");

  // ----------------------------
  // 5. Control Logic
  // Fan Control (Temp > 30°C)
  if (Temp > 30) {
    digitalWrite(Fan_Pin, HIGH);
    lcd.setCursor(0, 3);
    lcd.print(" Fan:ON  ");
  } else {
    digitalWrite(Fan_Pin, LOW);
    lcd.setCursor(0, 3);
    lcd.print(" Fan:OFF ");
  }

  // Pump Control (Soil Moisture < 40% and No Rain)
  if (soilMoisture < 40 && rain == 0) {
    digitalWrite(Pump_Pin, HIGH);
    lcd.setCursor(10, 3);
    lcd.print(" Motor:ON ");
  } else {
    digitalWrite(Pump_Pin, LOW);
    lcd.setCursor(10, 3);
    lcd.print(" Motor:OFF");
  }

  delay(1000);  // Small delay for stability
}
