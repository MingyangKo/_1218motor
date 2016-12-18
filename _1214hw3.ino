#include <Wire.h>
#include <Servo.h> 

#define M 9

Servo myservo; 
int angle=0;

void setup() {
  Wire.begin(8); // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  myservo.attach(9); 
  Serial.begin(115200); // start serial for output
}


void loop() {
delay(50);
}


void receiveEvent(int howMany) {

angle = Wire.read(); // receive byte as an integer
Serial.println(angle); // print the integer
myservo.write(angle);

delay(15);

}
