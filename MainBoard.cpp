#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void new_situation();
void update_lcd();
void check_condition();

float temperature, humidity, last_temperature, last_humidity;
float motor_dc_speed = 0.0;
bool new_condition = false;

void setup() {
  // Initialise serial communication
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop() {

  if (Serial.available() > 4) // 5B = 1B Condition delimiter(T/H) + 4B Float
    new_situation();

  if(new_condition){
    new_condition = false;
    check_condition();
    update_lcd();
  }

  last_temperature = temperature;
  last_humidity = humidity;

}

void new_situation(){

  char request = Serial.read();
  // Read temperature
  if(request == 'T'){
    temperature = Serial.parseFloat();
    if(temperature != last_temperature)
      new_condition = true;
  }
  // Read humidity
  else if(request == 'H'){
    humidity = Serial.parseFloat();
    if(humidity != last_humidity)
      new_condition = true;
  }
}

void check_condition(){
  if(humidity > 50)
    motor_dc_speed = 0;

  else if(humidity < 20)
    motor_dc_speed = 64; // %25 duty cycle
  
  else if(temperature > 25)
    motor_dc_speed = 26; // %10 duty cycle

  else
    motor_dc_speed = 0;

  Serial.print('S');
  Serial.println(motor_dc_speed);
}


void update_lcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if(motor_dc_speed == 64)
    lcd.println("Water: 20 cc/min");
  
  else if(motor_dc_speed == 26)
    lcd.println("Water: 10 cc/min");
  
  else
    lcd.println("Water: 0 cc/min");

  lcd.setCursor(0, 1);
  lcd.print("Motor Speed: ");
  lcd.print(motor_dc_speed);
}