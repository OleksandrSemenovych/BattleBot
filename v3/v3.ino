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

#define BLACK 900 // defines the threshold of when we say the colour sensor senses the colour black

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < sensorCount; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  // Read sensor values
  for (int i = 0; i < sensorCount; ++i) {
    sensorValues[i] = analogRead(sensorPins[i]);
  }

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
    isAttempingToGetOntTrack = true;
    raceStarted = true;
    moveForward();
    delay(800);
    moveGripper(80);
  } 
  else if (isAttempingToGetOntTrack){
    if(sensorValues[0] < BLACK || sensorValues[1] < BLACK){
      isAttempingToGetOntTrack = false;
    } else{
      turnAround();
    }
  }
  else if(raceStarted){
    if (distance < 15){
      avoidObject();
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
  analogWrite (motorPin1, 200);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void moveLeft() {
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
  moveRight();
  delay (500);
  moveForward();
  delay (1000);
  moveLeft();
  delay (1000);
  moveForward();
  delay (1000);
  moveLeft();
  delay (1000);
  while ((sensorValues[2] == 0) || (sensorValues[3] == 0) || (sensorValues[4] == 0) || (sensorValues[5] == 0)){
    moveForward ();
  }
  moveRight();
  delay (300);
}
