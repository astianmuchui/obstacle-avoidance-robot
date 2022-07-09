#include <Arduino.h>
/*
  Arduino uno obstacle avoiding robot 
  This version is not controllable , just runs on its own 
  
*/

// Declare pins

// MOTOR 1 

const int EN1 = 2;     
const int IN1A = 3;
const int IN1B = 5;

// MOTOR 2
const int EN2 = 4;        
const int IN2A = 6;
const int IN2B = 10;

int pins[6] = {2,3,5,4,6,10};

const int echo_sensor_pin = 11; 
const int trigger_sensor_pin = 12;
int limit =  20;
void setup() {
  // Set all the motor pins to output pins 
  for(int pin = 0; pin <6; pin++){
    pinMode(pins[pin],OUTPUT);
  }
  pinMode(echo_sensor_pin, INPUT);
  pinMode(trigger_sensor_pin,OUTPUT);
  
}

void loop() {
  
  digitalWrite(trigger_sensor_pin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigger_sensor_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_sensor_pin,LOW);
  // Read Echo PIN
  
  int ultrasonic_duration = pulseIn(echo_sensor_pin,HIGH);
  int distance = ultrasonic_duration * 0.034 /2;
  
  if(distance > limit){
    do{
      Forward();
    }while(distance > limit+5);
  }else{
    AdjustDistance(limit,distance);
  }
  
}

void AdjustDistance(int limit , int distance){
 // Move backwards and then turn check where to go
  Backward();
  delay(1000);
  
  // Turn left 
  Left();
  delay(100);
  int distanceL = read_distance();
  delay(100); 
  
  Right();
  
  delay(100);
  int distanceR = read_distance();
  delay(100);
  
  if(distanceR > distanceL){
    // Since it had moved right previously , no need to turn again 
      Forward();
  }else if(distanceL>distanceR){
    // Move left then forward 
    Left();
    delay(1000);
    Forward();
  }else{
    // Recursion
    AdjustDistance(limit,distance);
  }
    
  
}

int read_distance(){
  int ultrasonic_duration = pulseIn(echo_sensor_pin,HIGH);
  int distance = ultrasonic_duration * 0.034 /2;
  return distance;
}
void Switch_ON()
{
  digitalWrite(EN1, HIGH );
  digitalWrite(EN2, HIGH );
}


void Switch_OFF()
{
  digitalWrite(EN1, LOW );
  digitalWrite(EN2, LOW );
}

void Forward()
{
  digitalWrite(IN1A, HIGH); 
  digitalWrite(IN1B, LOW);

  digitalWrite(IN2A, HIGH); 
  digitalWrite(IN2B, LOW);
}

void Backward()
{
  digitalWrite(IN1A, LOW); 
  digitalWrite(IN1B, HIGH);

  digitalWrite(IN2A, LOW); 
  digitalWrite(IN2B, HIGH);
}

void Right()
{
  digitalWrite(IN1A, HIGH ); 
  digitalWrite(IN1B, LOW);

  digitalWrite(IN2A, LOW); 
  digitalWrite(IN2B, HIGH);
}

void Left()
{
  digitalWrite(IN1A, LOW);
  digitalWrite(IN1B, HIGH);

  digitalWrite(IN2A, HIGH); 
  digitalWrite(IN2B, LOW);
}

void Brake()
{
  digitalWrite(IN1A, LOW); 
  digitalWrite(IN1B, LOW);

  digitalWrite(IN2A, LOW); 
  digitalWrite(IN2B, LOW);
}