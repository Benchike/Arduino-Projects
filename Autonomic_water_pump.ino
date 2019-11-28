/* This code is an autonomatic water pump program meant to switch a solenoid Valve by controlling its relay */

#define Relay 13 // Intializes and defines the use of digital pin 13 to send signal to the relay
void setup() {
 // put your setup code here, to run once:

 pinMode(13, OUTPUT);
 // Setup digital pin 13 where the relay is connected as an output pin that will give out information

 Serial.begin(9600);
 // Intializes the IDE serial monitor to print statements from the result

}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println("WATER FLOW ENABLED");
// Communicates the serial monitor to print the statement showing the condition of the relay

digitalWrite(Relay, LOW);
/* Sends a digital signal to turn ON the relay which will also open up the Solenoid Valve to allow water
  passage to the plants */

delay(10000);
// Will turn the Solenoid Valve ON for the 1hr to ensure optimum and sufficient water supply to plants

Serial.println("WATER FLOW DISABLED");
//  Communicates the serial monitor to print the statement showing the condition of the relay

digitalWrite(Relay, HIGH);
/* Sends a digital siganl to turn OFF the relay which will also open up the Solenoid Valve to allow water
  passage to the plants */

delay(60000);
// Turns of the Solenoid Valve for the next 3hrs before the next water supply cycle
}
