if(sensorValues[1] > BLACK && sensorValues[2] > BLACK && sensorValues[3] > BLACK && sensorValues[4] > BLACK && sensorValues[5] > BLACK && sensorValues[6] > BLACK && sensorValues[7] > BLACK){
        moveForvard();
        delay(5); //calibrate this
        if(sensorValues[1] > BLACK && sensorValues[2] > BLACK && sensorValues[3] > BLACK && sensorValues[4] > BLACK && sensorValues[5] > BLACK && sensorValues[6] > BLACK && sensorValues[7] > BLACK){
            finish();
          }
      } 


      
void finish (){
  moveGripper(0);
  moveBackwards();
  delay(100);
}
