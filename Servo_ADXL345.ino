 // Include the Servo library
#include <Servo.h> 
#include <ADXL345.h>

ADXL345 accel;
char hs;

// Declare the Servo & Switch pin
int servoPin1 = 3;
int servoPin2 = 4;
int servoPin3 = 5;

const int s1Pin = 8;
const int s2Pin = 9;
const int s3Pin = 10;
int s1State = 0;
int s2State = 0;
int s3State = 0;
int pos1 = 0;    // variable to store the servo1 position
int pos2 = 0;    // variable to store the servo2 position
int pos3 = 0;    // variable to store the servo3 position

// Create a servo object
Servo Servo1;
Servo Servo2;
Servo Servo3;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(s1Pin, INPUT);
  pinMode(s2Pin, INPUT);
  pinMode(s3Pin, INPUT);
  
  Serial.begin(9600);
  Wire.begin();
  // We need to attach the servo to the used pin number
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
  Servo3.attach(servoPin3);
  // Caliberate Accilerometer
  accel.init(-1, 0, 8);
  accel.setSoftwareOffset(-0.023, 0, 0.03577027);
  accel.printCalibrationValues(40);

    // Make servo go to initial position : 90 degree in code and 0 degree wrt reference

    Servo1.write(86);
    delay(500);

    Servo2.write(4);
    delay(500);

    Servo3.write(90);
    delay(500);
}

void loop(){
  
int i;
float pitch=0, roll = 0;
    /*  hs = 0;
         while(hs != '1')
            {
              hs = Serial.read();
            } */
            
      //Aquire data
     // AccelG accelG;
     // accelG = accel.readAccelG();
    
    for(i=1;i<100;i++)
    {  
      AccelRotation accelRot;
      accelRot = accel.readPitchRoll();
      if(accelRot.pitch >= 0)
      {
        pitch = ((pitch + accelRot.pitch)/2);
      }
      if(accelRot.roll >= (-90))
      {
        roll = ((roll + accelRot.roll)/2);
      }
     }
    int pAngle = pitch;
    int rAngle = roll;
 
   //     int a = (pAngle/2.5);               // for rounding the pitch angle to near by value which is multiple of 5s
   //     pAngle = ((( a/2)*5)+((a%2)*5));

   //     int b = (rAngle/2.5);               // for rounding the roll angle to near by value which is multiple of 5s
   //     rAngle = ((( b/2)*5)+((b%2)*5));       
   
     // read the state of the pushbutton value:
    s1State = digitalRead(s1Pin);
    s2State = digitalRead(s2Pin);
    s3State = digitalRead(s3Pin); 
    
    if(s1State == LOW )
    {
    Serial.print(" 1 : "); 
    Serial.println(pAngle);

      pAngle = ( 86 - pAngle );
    
    pos1 = Servo1.read();
      if(pAngle>pos1)
      {
        for (i = pos1; i <= pAngle; i++)  
        {
          Servo1.write(i); 
          delay(15);
        } 
      }
      else if(pAngle<pos1)
      {
        for (i = pos1; i >= pAngle; i--)  
        {
          Servo1.write(i); 
          delay(15);
        }      
      }
    }
    else if(s2State == LOW)
    {

    
    Serial.print(" 2 : ");
    Serial.println(pAngle);
     
      pAngle = (4 + pAngle);

    pos2 = Servo2.read();
      if(pAngle>pos2)
      {
        for (i = pos2; i <= pAngle; i++)   
        {
          Servo2.write(i); 
          delay(15);
        } 
      }
      else if(pAngle<pos2)
      {
        for (i = pos2; i >= pAngle; i--)  
        {
          Servo2.write(i); 
          delay(15);
        }      
      }
    }

    else if(s3State == LOW)
    {  
    Serial.print(" 3 : ");
    Serial.println(rAngle);
     
      rAngle = (90 + rAngle);

    pos3 = Servo3.read();
      if(rAngle>pos3)
      {
        for (i = pos3; i <= rAngle; i++)   
        {
          Servo3.write(i); 
          delay(15);
        } 
      }
      else if(rAngle<pos3)
      {
        for (i = pos3; i >= rAngle; i--)  
        {
          Servo3.write(i); 
          delay(15);
        }      
      }
    }    
}

