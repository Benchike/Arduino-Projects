#define leftForwardTire 10
#define leftBackwardTire 9
#define rightForwardTire 6
#define rightBackwardTire 5

#define lefts A4 
#define rights A5

int Speed=100;
void setup() {
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  Serial.begin(9600);
}
void loop(){
  
 Serial.println("left"+String(analogRead(lefts)));
 Serial.println("right"+String(analogRead(rights)));
 
  
  //line detected by both
  if(analogRead(lefts)<=400 && analogRead(rights)<=400){
    //stop
    Stop();
  moveForward();
  delay(100); 
  }
  //line detected by left sensor
  else if(analogRead(lefts)>=400 && analogRead(rights)<=400){
    //turn left
    Stop();
    delay(200);
    turnRight(200);
    delay(100);
     
  }
  //line detected by right sensor
  else if(analogRead(lefts)<=400 && analogRead(rights)>=400){
    //turn right
    Stop();
    delay(200);
    turnLeft(200);
   
   delay(100);
  }
  //line detected by none
  else {
    //stop
    Stop();
  }
}

/////////////////////////////////////////////////////////////////////////
void turnRight(int Speedn){
     analogWrite(leftForwardTire,0);
     analogWrite(rightForwardTire,Speedn);
     analogWrite(leftBackwardTire,Speedn);
     analogWrite(rightBackwardTire,0);
   
  }

 void turnLeft(int Speedn){
     analogWrite(leftForwardTire,Speedn);
     analogWrite(rightForwardTire,0);
     analogWrite(leftBackwardTire,0);
     analogWrite(rightBackwardTire,Speedn);
     
  }

 void Stop(){
    
     analogWrite(leftForwardTire,0);
     analogWrite(rightForwardTire,0);
     analogWrite(leftBackwardTire,0);
     analogWrite(rightBackwardTire,0);
  }
 void moveForward(){
     analogWrite(leftForwardTire,100);
     analogWrite(rightForwardTire,100);
     analogWrite(leftBackwardTire,0);
     analogWrite(rightBackwardTire,0);
  }
  
