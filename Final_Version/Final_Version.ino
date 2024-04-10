#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUMPIXELS 4

#define LEFT_BACK_LED 0
#define LEFT_FRONT_LED 3

#define RIGHT_BACK_LED 1
#define RIGHT_FRONT_LED 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int motorPin1 = 10;   // Motor 1 control pin
const int motorPin2 = 11;   // Motor 1 control pin
const int motorPin3 = 6;   // Motor 2 control pin
const int motorPin4 = 5;   // Motor 2 control pin

const int trigPin = 4; // Connect Trig to digital pin 2
const int echoPin = 2; // Connect Echo to digital pin 7

const int servoPin = 9; // Servo control pin

const int sensorCount = 8; // Number of sensors in your analog line sensor
const int sensorPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7}; // Analog sensor pins
int sensorValues[sensorCount]; // Array to store sensor values

bool isAttempingToGetOntTrack = false;
bool raceStarted = false;
bool isLeft = false;
bool isRight = false;
bool isGettingOnLine = false;
bool isEndPart = false;

#define BLACK 900 // defines the threshold of when we say the colour sensor senses the colour black

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  strip.begin();
  strip.show();

  for (int i = 0; i < sensorCount; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void readSensors(){
  for (int i = 0; i < sensorCount; ++i) {
    sensorValues[i] = analogRead(sensorPins[i]);
  }
  }

void loop() {
  // Read sensor values
  readSensors();

  // Triggering the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reading the pulse duration from Echo pin
  long duration = pulseIn(echoPin, HIGH);

  float theSpeedOfSound = 0.034; //centimeters per microsecond
  // Calculating distance in centimeters
  int distance = duration * theSpeedOfSound / 2; //We divided it by 2 
  //because the signal has travelled to the target and back, 
  //so the distance is the total round-trip distance

if(!raceStarted && distance > 23){
    strip.setPixelColor(LEFT_BACK_LED, strip.Color(0, 3, 0));
    strip.setPixelColor(LEFT_FRONT_LED, strip.Color(0, 255, 0));
    strip.setPixelColor(RIGHT_BACK_LED, strip.Color(0, 3, 0));
    strip.setPixelColor(RIGHT_FRONT_LED, strip.Color(0, 255, 0));

    strip.show();
    isAttempingToGetOntTrack = true;
    raceStarted = true;
    moveForward();
    delay(800);
    moveGripper(80);
    moveLeft();
    delay(500);
  } 
  else if (isAttempingToGetOntTrack){
    if(sensorValues[0] < BLACK || sensorValues[1] < BLACK || (sensorValues[0] < BLACK && sensorValues[1] < BLACK)){
      isAttempingToGetOntTrack = false;
    } else{
      turnAround();
    }
  }
  
  else if(isEndPart && (sensorValues[1] > BLACK && sensorValues[2] > BLACK) && (sensorValues[5] > BLACK && sensorValues[6] > BLACK)){
        moveForward();
        delay(100); //calibrate this
        readSensors();
        if ((sensorValues[1] > BLACK && sensorValues[2] > BLACK) && (sensorValues[3] > BLACK && sensorValues[4] > BLACK) && (sensorValues[5] > BLACK && sensorValues[6] > BLACK) && sensorValues[7] > BLACK){
           delay(100); //calibrate this
           readSensors();
            if ((sensorValues[1] > BLACK && sensorValues[2] > BLACK) && (sensorValues[3] > BLACK && sensorValues[4] > BLACK) && (sensorValues[5] > BLACK && sensorValues[6] > BLACK) && sensorValues[7] > BLACK){
                finish();
            }
            else{
                moveForward();
              } 
          }
          else{
              moveForward();
            } 
      } 
  else if(raceStarted){
    if (distance < 15){
      avoidObject();
      stopRobot();
      delay(1000);
    }
    else{
      if(sensorValues[3] > BLACK || sensorValues[4] > BLACK){
        moveForward();
      } 
      else if(sensorValues[0] > BLACK || sensorValues[1] > BLACK || sensorValues[2] > BLACK){
        moveRight();
        isRight = true;
        isLeft = false;
      } 
      else if(sensorValues[7] > BLACK || sensorValues[6] > BLACK || sensorValues[5] > BLACK){
        moveLeft();
        isLeft = true;
        isRight = false;
      } 
      else{
        findLine();
        }
      }
    }
}

//Activated the gripper
void moveGripper(int angle) {
  int pwmValue = map(angle, 0, 180, 0, 255);
  analogWrite(servoPin, pwmValue);
}

void stopRobot() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void findLine() {
  if(isLeft){
    moveLeft();
  }else if(isRight){
    moveRight();
  }else
  moveBackwards();
}

void moveForward() {
  strip.setPixelColor(LEFT_BACK_LED, strip.Color(0, 255, 0));
  strip.setPixelColor(LEFT_FRONT_LED, strip.Color(0, 255, 0));
  strip.setPixelColor(RIGHT_BACK_LED, strip.Color(0, 255, 0));
  strip.setPixelColor(RIGHT_FRONT_LED, strip.Color(0, 255, 0));

  strip.show();
  analogWrite (motorPin1, 255);
  digitalWrite(motorPin2, LOW);
  analogWrite (motorPin3, 247);
  digitalWrite(motorPin4, LOW);
}

void moveBackwards() { 
  digitalWrite(motorPin1, LOW);
  analogWrite(motorPin2, 170);
  digitalWrite(motorPin3, LOW);
  analogWrite(motorPin4, 180);
}

void moveRight() {
  strip.setPixelColor(LEFT_BACK_LED, strip.Color(0, 3, 0));
  strip.setPixelColor(LEFT_FRONT_LED, strip.Color(0, 3, 0));
  strip.setPixelColor(RIGHT_BACK_LED, strip.Color(0, 255, 0));
  strip.setPixelColor(RIGHT_FRONT_LED, strip.Color(0, 255, 0));

  strip.show();
  analogWrite (motorPin1, 200);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void moveLeft() {
  strip.setPixelColor(LEFT_BACK_LED, strip.Color(0, 255, 0));
  strip.setPixelColor(LEFT_FRONT_LED, strip.Color(0, 255, 0));
  strip.setPixelColor(RIGHT_BACK_LED, strip.Color(0, 3, 0));
  strip.setPixelColor(RIGHT_FRONT_LED, strip.Color(0, 3, 0));

  strip.show();
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite (motorPin3, 200);
  digitalWrite(motorPin4, LOW);
}

// TurnAround also is TurnLeft
void turnAround() {
  digitalWrite(motorPin1, LOW);
  analogWrite (motorPin2, 170);
  analogWrite (motorPin3, 130);
  digitalWrite(motorPin4, LOW);
}

void avoidObject() {
  isEndPart = false;
  moveRight();
  delay (500);
  moveForward();
  delay (500);
  moveLeft();
  delay (500);
  moveForward();
  delay (500);
  moveLeft();
  delay (600);
  isEndPart = true;
  while (sensorValues[7] > BLACK || sensorValues[6] > BLACK){
      moveForward();
      readSensors();
    }
    stopRobot();
    delay (1000);
    moveRight();
    delay (300);
    isRight = true;
    isLeft = false;
}

void finish (){
  moveBackwards();
  delay(250);
  stopRobot();
  moveGripper(140);
  moveBackwards();
  delay(2500);
  while (true){
      moveLeft();
      
      strip.setPixelColor(LEFT_BACK_LED, strip.Color(0, 255, 0));
      strip.setPixelColor(LEFT_FRONT_LED, strip.Color(0, 255, 0));
      strip.setPixelColor(RIGHT_BACK_LED, strip.Color(0, 255, 0));
      strip.setPixelColor(RIGHT_FRONT_LED, strip.Color(0, 255, 0));
     
      strip.show();
      delay (300);
      
      strip.setPixelColor(LEFT_BACK_LED, strip.Color(0, 255, 0));
      strip.setPixelColor(LEFT_FRONT_LED, strip.Color(0, 255, 0));
      strip.setPixelColor(RIGHT_BACK_LED, strip.Color(0, 3, 0));
      strip.setPixelColor(RIGHT_FRONT_LED, strip.Color(0, 3, 0));
      
      strip.show();
      moveRight;
      delay(300);     
  }
}
