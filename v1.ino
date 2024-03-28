#define LEFT_WHEEL_FORWARD 6 
#define LEFT_WHEEL_BACKWARDS 5 

#define RIGHT_WHEEL_FORWARD 10 
#define RIGHT_WHEEL_BACKWARDS   

int sensors[] = {0,0,0,0,0,0,0,0};

int sensorPins[] = {A7,A6,A5,A4,A3,A2,A1,A0};

void setup() {
  pinMode(LEFT_WHEEL_FORWARD, OUTPUT);
  pinMode(LEFT_WHEEL_BACKWARDS, OUTPUT);

  pinMode(RIGHT_WHEEL_FORWARD, OUTPUT);
  pinMode(RIGHT_WHEEL_BACKWARDS, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  Serial.begin(9600);
}

void loop() {
  solveMaze();
}

void checkSensorsValues(){
  for(int i = 0; i < sizeof(sensorPins)/sizeof(sensorPins[0]);i++){
    if(analogRead(sensorPins[i])>700){
      sensors[i]=1;
      }
    else{
      sensors[i]=0;
      }
      Serial.print(sensors[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

 void solveMaze(){
    checkSensorsValues();
        if(sensors[3] && sensors[4]){
            analogWrite(LEFT_WHEEL_FORWARD, 255);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 255);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
          }
        else if(sensors[0]){
         analogWrite(LEFT_WHEEL_FORWARD, 255);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 0);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 255);
          }
          else if(sensors[7]){
         analogWrite(LEFT_WHEEL_FORWARD, 0);
            analogWrite(LEFT_WHEEL_BACKWARDS, 255);
            analogWrite(RIGHT_WHEEL_FORWARD, 255);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
          }
         else if(sensors[6]){
         analogWrite(LEFT_WHEEL_FORWARD, 255);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 140);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
          }
        else if(sensors[1]){
            analogWrite(LEFT_WHEEL_FORWARD, 140);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 255);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
        }
        else if(sensors[5]){
            analogWrite(LEFT_WHEEL_FORWARD, 255);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 230);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
            }
        else if(sensors[2]){
            analogWrite(LEFT_WHEEL_FORWARD, 230);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 255);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
            }
        else if(sensors[4] && !sensors[3]){
            analogWrite(LEFT_WHEEL_FORWARD, 255);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 240);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
            }
        else if(sensors[3] && !sensors[4]){
            analogWrite(LEFT_WHEEL_FORWARD, 240);
            analogWrite(LEFT_WHEEL_BACKWARDS, 0);
            analogWrite(RIGHT_WHEEL_FORWARD, 255);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 0);
            }
        else{
            analogWrite(LEFT_WHEEL_FORWARD, 0);
            analogWrite(LEFT_WHEEL_BACKWARDS, 255);
            analogWrite(RIGHT_WHEEL_FORWARD, 0);
            analogWrite(RIGHT_WHEEL_BACKWARDS, 255);
            }
}
