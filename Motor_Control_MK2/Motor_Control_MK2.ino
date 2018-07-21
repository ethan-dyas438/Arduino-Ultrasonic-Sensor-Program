/*
This program goes forward until it detects an object less than 20cm away
from it, then backs up for 4 seconds, then it turns
left for 1 second, then goes forward for 3 seconds.  Therefore this
program is written to avoid an obstacle when it first goes forward.
*/
int enB = 8;//enable B is set to pin 8
int enA = 31;//enable A is set to pin 31
int LMF = 12;//Left Motor Forward is set to pin 12
int LMR = 11;//Left Motor Reverse is set to pin 11
int RMF = 10;//Right Motor Forward is set to pin 10
int RMR = 9;//Right Motor Reverse is set to pin 9
int pingpin = 7;//ultrasonic sensor is set to pin 7
int buttonPin = 4;//button is set to pin 4
int buttonState = 0;//the botton's state is set to LOW
long mtrrevtim = 0;//motor reverse timer is set to LOW
int forwardhold = 0;//forward palceholder is set to LOW
int reversehold = 0;//reverse placeholder is set to LOW
int turnfor = 0;//turnforward placeholder is set to LOW

void setup() {
  Serial.begin(9600);//activates serial moniter
 pinMode(buttonPin, INPUT);//button as input
 pinMode(enB, OUTPUT);//enable B as output
 pinMode(enA, OUTPUT);//enable A as output
 pinMode(LMF, OUTPUT);//Left Motor Forward as output
 pinMode(LMR, OUTPUT);//Left Motor Rverse as output
 pinMode(RMF, OUTPUT);//right motor forward as output
 pinMode(RMR, OUTPUT);//right motor reverse as output
 digitalWrite(LMF, LOW);//Left Motor Forward is set to LOW
 digitalWrite(LMR, LOW);//Left Motor Reverse is set to LOW
 digitalWrite(RMF, LOW);//right motor forward is set to LOW
 digitalWrite(RMR, LOW);//right motor reverse is set to LOW
 digitalWrite(enA, HIGH);//enable A is set to high
 digitalWrite(enB, HIGH);//enable B is set to low
 forwardhold = 0;//forward placeholder is set to low
 reversehold = 0;//reverse placeholder is set to low
 turnfor = 0;//makes turnforward placeholder low
 
}

void loop() {
  
 buttonState = digitalRead(buttonPin);//botton state reads button pin

if (buttonState == HIGH){//if button is pushed
 forwardhold = 1; //turn forward place holder high
}

//if forward placeholder is high and reverse placeholder is low
if(forwardhold == HIGH && reversehold == LOW) {
  mtrrevtim = 0;//make motor reverse timer 0
  forwardSub();//go into forwardSub
}

//if reversehold is high and forwardhold is low
if (reversehold == HIGH && forwardhold == LOW){
    reverseSub();//go into reverse sub
  }
  
//both reversehold and forwardhold need to be low and turnfor needs to be high
if (reversehold == LOW && forwardhold == LOW && turnfor == HIGH){
  turnforwardSub();//goes to turnforward Subroutine
}

}

void forwardSub() {//forward sub
 digitalWrite(LMF, HIGH);//turn left motor on forward
digitalWrite(RMF, HIGH);//tun right motor on forward

long duration, inches, cm;//duration is counted in inches and cm
 
 pinMode(pingpin, OUTPUT);//pingpin is a output
 digitalWrite(pingpin, LOW);//ping pin set to low
 delayMicroseconds(2);//delay for two microseconds
 digitalWrite(pingpin, HIGH);//turn pingpin high
 delayMicroseconds(5);//dealy for five microseconds
 digitalWrite(pingpin, LOW);//turn pingpin low
 
 pinMode(pingpin, INPUT);//pingpin is a input
 duration = pulseIn(pingpin, HIGH);//duration is pulsed when pingpin is high
 
 //inches is the duration of microseconds to inches
 inches = microsecondsToInches(duration);
 
 //cm is the duration of microseconds to cm
 cm = microsecondsToCentimeters(duration);
 
  Serial.print(inches);//print in inches
 Serial.print("in, ");//print in,
 Serial.print(cm);//print in cm
 Serial.print("cm");//print cm
 Serial.println();//print a blank line
 delay(100);//delay 0.1 seconds
 
 if (cm < 20){//if cm is less than 20
   forwardhold = 0;//make forward placeholder low
   reversehold = 1;//make reverse palceholder high
 
 
 }
}

void reverseSub() {//reversesub
  digitalWrite(LMF, LOW);//turn left motor forward off
  digitalWrite(RMF,LOW);//turn right motor forward off
  delay(1000);//delay for 1 second
  digitalWrite(LMR, HIGH);//turn left motor reverse on
  digitalWrite(RMR, HIGH);//turn right motor reverse on
  delay(4000);//delay for 4 seconds
  digitalWrite(LMR, LOW);//turn left motor reverse off
  digitalWrite(RMR, LOW);//turn right motor reverse off
  reversehold = 0;//make reverse palceholder low
  turnfor = 1;//makes turnfor high
}

void turnforwardSub() {//turns then moves forward
  digitalWrite(RMF, HIGH); //turns right motor forward
  delay(1000);//waits for 1 seconds
  digitalWrite(RMF, LOW); //turns right motor off
  delay(1000);//waits for one second
  digitalWrite(LMF, HIGH);//turns left motor forward on
  digitalWrite(RMF, HIGH);//turns right motor forward on
  delay(3000);//waits for 3 seconds
  digitalWrite(LMF, LOW);//turns right motor forward off
  digitalWrite(RMF, LOW);//turns right motor forward off
  turnfor = 0;//makes turnfor low
}

//turn microseconds to "microseconds to inches"
long microsecondsToInches(long microseconds)
{
 return microseconds / 74 / 2;//microseconds divided by 74 divided by 2
}

//turn microseconds to "microseconds to cm"
long microsecondsToCentimeters(long microseconds)
{
 return microseconds / 29 / 2;//micorseconds divided by 29 divided by 2
}



