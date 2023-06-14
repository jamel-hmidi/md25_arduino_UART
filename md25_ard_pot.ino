/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : md25_ard_pot.ino
  ******************************************************************************
  * 
  * 2023
  * Jamel HMIDI
  * Microelectronis and Embedded Systems Engineering Student
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include <SoftwareSerial.h>

SoftwareSerial md25Serial(10, 11);  // RX: Arduino pin 10 (connected to MD25 TX), TX: Arduino pin 11 (connected to MD25 RX)
const int potPin = A0;              // Analog input pin for the potentiometer

void setup() {
  Serial.begin(9600);
  md25Serial.begin(9600);
}

void loop() {

  // Map Pot Value to Speed
  int potValue = analogRead(potPin);             // Read the potentiometer value
  int motorSpeed = map(potValue, 0, 1023, 0, 255); // Map the potentiometer value to motor speed range

  // Set motor speeds
  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x31));   // SET SPEED 1 command
  md25Serial.write(static_cast<uint8_t>(motorSpeed));    // Motor 1 speed

  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x32));   // SET SPEED 2 command
  md25Serial.write(static_cast<uint8_t>(motorSpeed));    // Motor 2 speed

 // delay(100);  // Delay for smoother control
  
  // Read battery voltage
  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x26));   // GET VOLTS command

  delay(10);  // Wait for the response

  // Read the response from MD25
  while (md25Serial.available()) {
    Serial.print("Battery Voltage: ");
    Serial.print(md25Serial.read() / 10.0);  // Divide by 10 to get the actual voltage
    Serial.println("V");
  }

  // Read motor speeds
  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x21));   // GET SPEED 1 command

  delay(10);  // Wait for the response

  // Read the response from MD25
  while (md25Serial.available()) {
    Serial.print("Motor 1 Speed: ");
    Serial.print(md25Serial.read());
    Serial.println();
  }

  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x22));   // GET SPEED 2 command

  delay(10);  // Wait for the response

  // Read the response from MD25
  while (md25Serial.available()) {
    Serial.print("Motor 2 Speed: ");
    Serial.print(md25Serial.read());
    Serial.println();
  }

  // Read encoder values
  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x23));   // GET ENCODER 1 command

  delay(10);  // Wait for the response

  // Read the response from MD25
  long encoder1 = 0;
  while (md25Serial.available()) {
    encoder1 += md25Serial.read() << 24;
    encoder1 += md25Serial.read() << 16;
    encoder1 += md25Serial.read() << 8;
    encoder1 += md25Serial.read();
  }

  md25Serial.write(static_cast<uint8_t>(0x00));   // Sync byte
  md25Serial.write(static_cast<uint8_t>(0x24));   // GET ENCODER 2 command

  delay(10);  // Wait for the response

  // Read the response from MD25
  long encoder2 = 0;
  while (md25Serial.available()) {
    encoder2 += md25Serial.read() << 24;
    encoder2 += md25Serial.read() << 16;
    encoder2 += md25Serial.read() << 8;
    encoder2 += md25Serial.read();
  }

  Serial.print("Encoder 1: ");
  Serial.println(encoder1);
  Serial.print("Encoder 2: ");
  Serial.println(encoder2);

  delay(1000);
}
