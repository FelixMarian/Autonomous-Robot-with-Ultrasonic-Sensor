#include <Servo.h>


Servo leftWheel; //Servo object used for left wheel
Servo rightWheel; //Servo object used for right wheel

//Variable declaration
const int leftWheelSignal = 12;
const int rightWheelSignal = 11;
const int trigPin = 2;  
const int echoPin = 3; 
float duration, distance;

void setup() {
  DDRB = B00011000; //Setting Digital-Pins 11 and 12 as OUTPUTS
  DDRD = B00000100; //Setting Digital-Pins 2 as OUTPUT and 3 as INPUT
  leftWheel.attach(leftWheelSignal); //Attach leftWheel servo to pin 12;
  rightWheel.attach(rightWheelSignal); //Attach rightWheel servo to pin 11;
  Serial.begin(9600); //Serial communication 
}

void loop() {
  sendSonicSignals(); //Sending sonic signals using the ultrasonic sensor
  //Recieving the duration in which the ultrasonic sensor recieves the sonic signal
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration * 0.0343) / 2;  //Calculating the distance based on duration
 if (distance > 20) { //Check if the object is further than 20cm away
    //LeftWheel goes at MaxSpeed and RightWheel at -MaxSpeed thanks to the physical configuration of the robot
    leftWheel.writeMicroseconds(2000); 
    rightWheel.writeMicroseconds(1000);
  }
  else { 
    //If the object is closer than 20 cm to the robot, it will turn right around its own axis for one second
    for(int i=0;i<2;i++){
    	leftWheel.writeMicroseconds(1600);
        rightWheel.writeMicroseconds(1600);
        delay(500);
    }
  }
  //Print in the serial monitor the distance for debugging
  Serial.print("Distance: ");  
  Serial.println(distance);  
  delay(2);  
}

// This function sends sonic signals using an ultrasonic sensor
// It triggers the sensor by sending a pulse through the trigPin
void sendSonicSignals() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}
