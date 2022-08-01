// Controllable Version : Install dabble app from playstore
#include <NewPing.h>
// Bluetooth module to control the car using a phone
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#define PWM1_Ch1    0    
#define PWM1_Ch2    1
#define PWM1_Res   8      
#define PWM1_Freq  5000

int EN1 = 14;     
int IN1A = 12;
int IN1B = 13;
int EN2 = 5;      
int IN2A = 19;
int IN2B = 21;

int limit = 15; 

// @params 
// 1st -> trigger pin
// 2nd -> echo pin
// 3rd -> max area

NewPing sonar(10,11,20);
int ultrasonic_distance = sonar.ping_cm();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dabble.begin("Device_name");
  delay(50);
  pinMode(EN1, OUTPUT);  
  pinMode(IN1A, OUTPUT);
  pinMode(IN1B, OUTPUT);

  pinMode(EN2, OUTPUT);  
  pinMode(IN2A, OUTPUT);
  pinMode(IN2B, OUTPUT);

  Serial.println(" SWITCHING ON and setting speed  ");

  Motor_Speed(255);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Obstacle distance: ");
  Serial.println(sonar.ping_cm());
  delay(500);
  Dabble.processInput();
  if (GamePad.isUpPressed())
  {
    // Move robot forwards considering the ultrasonic distance
    if(ultrasonic_distance >limit)
    {
       do {
        Forward();
        delay(250);
        Brake();
      }while(ultrasonic_distance>limit);
      }
      else
      {
        Backward();
        delay(200);
        Left();
        delay(300);
        Brake();
        }
    }
    if (GamePad.isDownPressed())
    {
      if (ultrasonic_distance > limit)
      {
        do {
          Backward();
          delay(200);
        }while(ultrasonic_distance>limit);
        }else{
          // Probably not very neccesary since moving backwards increases the distance
          }

      }
      if (GamePad.isLeftPressed())
      {
        if (ultrasonic_distance >limit)
        {
          do {
            Left();
            delay(200);
            Brake();
            }while(ultrasonic_distance>limit);  
          }else{
            // Move back to allow room for turning
            Serial.println("Moving backwards to allow room for turning.....");
            Backward();
            delay(200);
            Serial.println("Moving left ......");
            Left();
            delay(200);
            Brake();
            }
          
        }
        if (GamePad.isRightPressed())
        {
          if (ultrasonic_distance > limit)
          {
            do {
              Right();
              delay(200);
              Brake();
              }while(ultrasonic_distance>limit);
            }else{
              // Move back to provide room for turning
              Serial.println("Moving backwards to allow room for turning....");
              Backward();
              delay(200);
              Serial.println("Moving Right ....");
              Right();
              delay(200);
              Brake();
         
              }

          
          }
        
    
}
void Switch_ON()
{
  digitalWrite(EN1, HIGH );
  digitalWrite(EN2, HIGH );
}

// SET SPEED
void Motor_Speed(int dutyCycle)
{
  ledcWrite(PWM1_Ch1, dutyCycle); // Setting motor 1 speed
  ledcWrite(PWM1_Ch2, dutyCycle);  // Setting motor 2 speed

}

// TURN OFF MOTORS
void Switch_OFF()
{
  digitalWrite(EN1, LOW );
  digitalWrite(EN2, LOW );
}

// Forward
void Forward()
{
  digitalWrite(IN1A, HIGH); // TURNING MOTOR 1 FORWARD
  digitalWrite(IN1B, LOW);

  digitalWrite(IN2A, HIGH); // TURNING MOTOR 2 FORWARD
  digitalWrite(IN2B, LOW);
}

// BACKWARD
void Backward()
{
  digitalWrite(IN1A, LOW); // TURNING MOTOR 1  BACK
  digitalWrite(IN1B, HIGH);

  digitalWrite(IN2A, LOW); // TURNING MOTOR 2  BACK
  digitalWrite(IN2B, HIGH);
}

// RIGHT
void Right()
{
  digitalWrite(IN1A, HIGH ); // TURNING MOTOR 1  FORWARD
  digitalWrite(IN1B, LOW);

  digitalWrite(IN2A, LOW); // TURNING MOTOR 2  BACKWARD
  digitalWrite(IN2B, HIGH);
}

// TURN ROBOT LEFT
void Left()
{
  digitalWrite(IN1A, LOW); // TURNING MOTOR 1  BACKWARD
  digitalWrite(IN1B, HIGH);

  digitalWrite(IN2A, HIGH); // TURNING MOTOR 2  FORWARD
  digitalWrite(IN2B, LOW);
}

// BRAKE
void Brake()
{
  digitalWrite(IN1A, LOW); // TURNING MOTOR 1 off
  digitalWrite(IN1B, LOW);

  digitalWrite(IN2A, LOW); // TURNING MOTOR 2 off
  digitalWrite(IN2B, LOW);
}
