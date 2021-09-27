#include<SoftwareSerial.h>

char i;
SoftwareSerial bluetooth(0,1);
#define enA 5
#define enB 6
#define in1 7
#define in2 8
#define in3 9
#define in4 11
#define LED 13
// right motors
int spdA = 170;
// left motors
int spdB = (0.689/0.69)*spdA - 15.12/0.69;
int x = 0;
void setup()
{
  bluetooth.begin(9600);
  Serial.begin(9600);
  // set all the motor control pins outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void forward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, spdA);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, spdB);
  x = 1;
  Serial.println(x);
}

void turnOff()
{
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
  x = 0;
  Serial.println(x);
}
void left()
{
  for (int i = 0; i <=15000; i++) {
  digitalWrite (in1, LOW);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, LOW);
  digitalWrite (in4, LOW);
  digitalWrite (enA, spdA);
  digitalWrite (enB, spdB);
}
delay(300);
}
void right()
{
  
  for (int i = 0; i <=15000; i++) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, spdA);
    analogWrite(enB, spdB);
  }
delay(300);
  
}
void backward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, spdA);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enB, spdB);
  x = 2;
  Serial.println(x);
}

void loop()
{
  if(bluetooth.available())
  {
    i = bluetooth.read();
   if(i == 'f')
 
     forward();

   else if(i == 'b')
   
     backward();
   
   else if(i == 'l'){
      if (x == 2) {
        left();
        delay(300);
        backward();

        }
      else if (x == 1){
        left();
        delay(300);
        forward();
      }
      else if (x == 0) {
        left();
        delay(300);
        turnOff();
      }
      }

   else if(i == 'r'){
      if (x == 2){
        right();
        delay(300);
        backward();

        }
      else if (x == 1){
        right();
        delay(300);
        forward();
        }
        
       else if (x == 0){
        right();
        delay(300);
        turnOff();
      }
   }
   else if(i == 'x') {
   
     turnOff();
   
  }
}
}
