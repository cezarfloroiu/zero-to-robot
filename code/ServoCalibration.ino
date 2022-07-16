// Find the width of the servo pulse (min & max)


// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>

// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  80  // Minimum value 80
#define SERVOMAX  600  // Maximum value 600

#define BUTTON 4
int currentServo = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("");    
    Serial.println("SERVO CALIBRATION");
    Serial.println("--------------------");
    Serial.println("Try pulse values on serial to find Min & Max");     
    Serial.println("");    
    Serial.print("Current servo = ");
    Serial.println(currentServo);    
    
    pinMode(BUTTON, INPUT);

    // Initialize PCA9685
    pca9685.begin();  
    // Set PWM Frequency to 50Hz
    pca9685.setPWMFreq(50);    

}

void loop() {
  
    while (Serial.available() == 0) {
      // wait for serial input
      
      int buttonState = digitalRead(BUTTON);
  
      if (buttonState == HIGH)
      {
        if (currentServo == 11) 
          currentServo = 0;
        else
          currentServo ++;
          
        delay(500);
        Serial.print("Current servo = ");
        Serial.println(currentServo);
  
      }     
    }
    int pulse = Serial.parseInt();
    Serial.print("Trying pulse value = ");
    Serial.println(pulse);
    
    //pwm0 = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    //pca9685.setPWM(currentServo, 0, pwm0);
    pca9685.setPWM(currentServo, 0, pulse);
    delay(25);

}
