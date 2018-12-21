/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);    
#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output,buffer, disp;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,1.2,2,0.6, DIRECT);

int select, reset;
int count=0;
double real,t1,t2;
void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(1);
  Serial.begin(9600);
   //lcd.begin(16, 2); 
  //Setpoint =629;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(20);

  
}

double realfunc ()
{
  if (Input>=625 && Input<=635)
  {
    real=0;
  }
  
  else if (Input>635)
  {
    real=((Input-630.5)/241.5)*60;
      }
  
  else if (Input>872)
  {
    real=60;
      }
  
  else if (Input<625)
  {
    real=((630.5-Input)/241.5)*-60;
      }
  
  else if (Input<389)
  {
    real=-60;
      }
      
  
 
 return real; 
}

void loop()
{
  t1=millis();
   buffer = analogRead(A1);
   Input=buffer;
 //  myPID.Compute();


select=digitalRead(4);
reset=digitalRead(7);

if (reset == LOW){
  Setpoint=analogRead(A2);
if (select == HIGH)
{  
  myPID.Compute();
  disp = realfunc();
}

else if(select == LOW)
{
   Output = map (Setpoint, 0, 1024, 0, 255);
   disp = realfunc();
}
}

else if (reset == HIGH)
{
Setpoint = 625;
disp = realfunc();
}
  
//  if(real>3)
//    real=((real-3)/1.1)*60;
//  if(real<3)
//    real=((3-real)/1.1)*(-60);
//   if(real==3)
//    real=0;
//  
  
  analogWrite(3,Output);
 // x=Input/10
 //Serial.print(Input);
 //Serial.print(" ");
 //Serial.print(Output);
 Serial.print(" ");
  Serial.println(disp);
  //Serial.println(" ");
  //t2=millis()-t1;
  //Serial.println(Setpoint);
 // Serial.print(millis());
  //Serial.print(" ");
}
