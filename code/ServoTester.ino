// Utility: test the servos using a potentionmeter

// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>

// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  195  // Minimum value 80
#define SERVOMAX  700  // Maximum value 600

// array of min/max pulses for each servo
// usually min is 80 and max is 600 but they vary from servo to servo so these values have to be found first
const int pulses [3][2] = { {80, 540}, {230, 525}, {80, 540} };


 //
#define POTENTIOMETER_PIN 34
#define BUTTON 4

// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;
int posDegrees;

int currentServo = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Running servo tester");   
    Serial.print("Current servo = ");
    Serial.println(currentServo);

    //
    pinMode(BUTTON, INPUT);

    // Initialize PCA9685
    pca9685.begin();
  
    // Set PWM Frequency to 50Hz
    pca9685.setPWMFreq(50);    

}

void loop() {
    int potValue = analogRead(POTENTIOMETER_PIN); // read the input on analog pin
    //Serial.println(potValue);

    int buttonState = digitalRead(BUTTON);

    if (buttonState == HIGH)
    {
      if (currentServo == 3) 
        currentServo = 0;
      else
        currentServo ++;
        
      delay(500);
      Serial.print("Current servo = ");
      Serial.println(currentServo);

    }

    int angle = potValue / 23;
    Serial.println(angle);
    
    pwm0 = map(angle, 0, 180, pulses[currentServo][0], pulses[currentServo][1]);
    pca9685.setPWM(currentServo, 0, pwm0);
    delay(25);

}
