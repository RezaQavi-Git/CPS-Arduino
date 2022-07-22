#include <Arduino.h>
#include <Wire.h>

#define SHT25_I2C_ADDRESS 0x40
#define CMD_TMP_NOHLD 0xF3
#define CMD_HUM_NOHLD 0xF5

float motor_dc_speed = 0.0;
float get_humidity();
float get_temperature();
void send_data(float, float);


void setup() {
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  // Initialise I2C communication
  Wire.begin();
  // Initialise serial communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 4) // 5B = 1B Condition Indicator(S) + 4B Float
    new_situation();

  float humidity = get_humidity();
  float temperature = get_temperature();

  analogWrite(9, motor_dc_speed);
  analogWrite(8, 0);

  send_data(humidity, temperature);
  // 5 minutes delay
  delay(5 * 60);
}

void new_situation(){

  char request = Serial.read();
  if(request == 'S'){
    motor_dc_speed = Serial.parseFloat();
  }
}

float get_humidity() {

  unsigned int data[2];  
  // Start I2C   
  Wire.beginTransmission(SHT25_I2C_ADDRESS);  
  // Send humidity measurement command, NO HOLD master  
  Wire.write(CMD_HUM_NOHLD);  
  // Stop I2C   
  Wire.endTransmission();  
  delay(500);
  // Request 2 bytes of data  
  Wire.requestFrom(SHT25_I2C_ADDRESS, 2);
  // humidity msb, humidity lsb
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();  
    data[1] = Wire.read();
    float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
    // Output data to Serial Monitor
    return humidity;
  }
}

float get_temperature() {
  unsigned int data[2];
  // Start I2C  
  Wire.beginTransmission(SHT25_I2C_ADDRESS);  
  // Send temperature measurement command, NO HOLD master  
  Wire.write(CMD_TMP_NOHLD);  
  // Stop I2C  
  Wire.endTransmission();  
  delay(500);
  // Request 2 bytes of data  
  Wire.requestFrom(SHT25_I2C_ADDRESS, 2);
  // temperature msb, temperature lsb  
  if(Wire.available() == 2)  
  {    
    data[0] = Wire.read();    
    data[1] = Wire.read();
    float temperature = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;    
    // Output data to Serial Monitor
    return temperature;
  }  
}

void send_data(float humidity, float temperature)
{
  Serial.print('H');
  Serial.println(humidity);
  Serial.print('T');
  Serial.println(temperature);
}