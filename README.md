# Arduino-Projects
Unmanned Ground Vehicle
#include <BitVoicer11.h>//incude bitvoicer library
#define lefts A4 
#define rights A5
#define leftForwardTire 10
#define leftBackwardTire 9
#define rightForwardTire 6
#define rightBackwardTire 5
#define trigPin 13
#define echoPin 12

boolean forward=false;
boolean backward=false;
boolean right=false;
boolean left=false;
boolean increasespeed=false;
boolean redusespeed=false;

int Speed=100;

BitVoicerSerial bvSerial = BitVoicerSerial();

void setup() {
 Serial.begin(9600);
 
 pinMode(lefts,INPUT);
 pinMode(rights,INPUT);
 pinMode(leftForwardTire,OUTPUT);
 pinMode(leftBackwardTire,OUTPUT);
 pinMode(rightForwardTire,OUTPUT);
 pinMode(rightBackwardTire,OUTPUT);
//////////////for the obstacle detection/////////
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
 bvSerial.getData();
  //Quits the loop if no string data was returned from getData
  if (bvSerial.strData == "")
  {
    return;
  }//end if
  
  if (bvSerial.strData == "mf")//move forward
  {  
    bvSerial.strData = "0";
    forward=true;
    moveForward();
   }//ends if
  else if(bvSerial.strData == "mb")//move back
  {
    bvSerial.strData = "0";
    backward=true;
    moveBack();
   }//ends else if
  else if(bvSerial.strData == "tl")//turn left
  {
    bvSerial.strData ="0";
    left=true;
    turnLeft(200);
   }//ends else if
   else if(bvSerial.strData == "st"){Speed=200;}
   else if(bvSerial.strData == "sm"){Speed=250;}
   else if(bvSerial.strData == "tr")//turn right
  {
    bvSerial.strData = "0";
    right=true;
    turnRight(200);
    
   }//ends else if
   else if(bvSerial.strData == "st")//stop
  {
    bvSerial.strData = "0";
    Stop();
   }//ends else if

   else if(bvSerial.strData == "ins")//increase Speed
  {
    bvSerial.strData = "0";
    increasespeed=true;
    increaseSpeed();
   }//ends else if

   else if(bvSerial.strData == "rs")//increase Speed
  {
    bvSerial.strData = "0";
    redusespeed=true;
    reduceSpeed();
   }//ends else if
  else{
    Stop();
    }
    detectObstacle();
}//ends loop

void moveForward(){
  if(forward){
     bvSerial.strData = "0";
     analogWrite(leftForwardTire,Speed);
     analogWrite(rightForwardTire,Speed);
     analogWrite(leftBackwardTire,0);
     analogWrite(rightBackwardTire,0);
     delay(2000);
     forward=false;
    }//ends if
   else{Stop();}
  }//ends method moveForward
  
void moveBack(){
    if(backward){
      bvSerial.strData = "0";
     analogWrite(leftForwardTire,0);
     analogWrite(rightForwardTire,0);
     analogWrite(leftBackwardTire,Speed);
     analogWrite(rightBackwardTire,Speed);
     delay(2000);
     backward=false;
    }//ends if
   else{Stop();}
  }
  
void turnLeft(int Speedt){
    if(left){
     bvSerial.strData = "0";
     analogWrite(leftForwardTire,Speed);
     analogWrite(rightForwardTire,0);
     analogWrite(leftBackwardTire,0);
     analogWrite(rightBackwardTire,Speed);
     delay(1000);
     left=false;
    }//ends if
   else{Stop();}
  }
  
void turnRight(int Speedt){
    if(right){
      bvSerial.strData = "0";
     analogWrite(leftForwardTire,0);
     analogWrite(rightForwardTire,Speed);
     analogWrite(leftBackwardTire,Speed);
     analogWrite(rightBackwardTire,0);
     delay(1000);
     right=false;
    }//ends if
   else{Stop();}
  }
void Stop(){
    
     analogWrite(leftForwardTire,0);
     analogWrite(rightForwardTire,0);
     analogWrite(leftBackwardTire,0);
     analogWrite(rightBackwardTire,0);
  }
  void increaseSpeed(){
    bvSerial.strData = "0";
    if(increasespeed){
    if(Speed<255){
    Speed+=50;}else{}
    increasespeed=false;
    }
    else{}
    }//ends void increase speed
    
 void reduceSpeed(){
    if(redusespeed){
      
    bvSerial.strData = "0";
    if(Speed>50){ Speed-=50;}else{}
    redusespeed=false;
    }
    else{}
    }// ends void reduce speed
    
 void detectObstacle(){
      long duration, distance;
      digitalWrite(trigPin, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
      //delayMicroseconds(1000); - Removed this line
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/2) / 29.1;  
      delay(5);
      }// ends detect obstacle
void followLine(){
if(analogRead(lefts)<=400 && analogRead(rights)<=400){
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
