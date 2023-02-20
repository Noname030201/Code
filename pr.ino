#include <Stepper_28BYJ.h>



#include <Servo.h> // подключаем библиотеку для работы с сервоприводом
int steps=-4078/8;

Servo servo1; // объявляем переменную servo типа "servo1"
int S0=4;
int S1=5;
int S2=8;
int S3=7;
int in1= 9;
int in2 =10;
int in3 =11;
int in4 =12;
int dl=5;
int on,onf;
int l1=-1;
int l2=-1;
int r1=-1;
int r2=-1;

int l,r;
int sensorOut=6;
bool ride=false;
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int sensColor;
bool white;
unsigned long currentTime; 
Stepper_28BYJ st(4078, 9, 10, 11, 12);  // объект motor, 48 шагов на оборот 
int redColor, greenColor, blueColor, whiteColor;

void setup() {
   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(in4, OUTPUT);
   pinMode(S0, 1);
   pinMode(S1, 1);
   pinMode(S2, 1);
   pinMode(S3, 1);
   pinMode(sensorOut, 0);
   st.setSpeed(100);
  // масштабирование 20%
   digitalWrite(S0,1);
   digitalWrite(S1,0);
   servo1.attach(13); // привязываем сервопривод к аналоговому выходу 11
   servo1.write(73);
   Serial.begin(9600);
   

}
boolean inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

void loop() {

  sensColor=0;
  if (Serial.available())
  {
    on=Serial.read();
    if(on!=0 && on!=1){
      onf=on/100;
      if(onf==0){
        ride=false;
        st.step(0);
      }
      if(onf==1){
        ride=true;
        st.step(steps);
        l=(on/10)%10;
        r=on%10;
        if(l==0){
          l1=2;
          l2=3;
        }
        if(l==1){
          l1=2;
          l2=4;
        }
        if(l==2){
          l1=2;
          l2=5;
        }
        if(l==3){
          l1=3;
          l2=4;
        }
        if(l==4){
          l1=3;
          l2=5;
        }
        if(l==5){
          l1=4;
          l2=5;
        }
        if(r==0){
          r1=2;
          r2=3;
        }
        if(r==1){
          r1=2;
          r2=4;
        }
        if(r==2){
          r1=2;
          r2=5;
        }
        if(r==3){
          r1=3;
          r2=4;
        }
        if(r==4){
          r1=3;
          r2=5;
        }
        if(r==5){
          r1=4;
          r2=5;
        }
        
        if(l>5 or r>5){
          l1=l-4;
          r1=r-4;
            
        }
      } 
    }
  }
  if(ride==true){
    st.step(steps);
  }
  if(ride==false){
    st.step(0);
  }
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, 20, 50, 255,0);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency,60, 90, 255, 0);
  

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency,40,70, 255, 0);
  if((greenColor > redColor) && (greenColor > blueColor)){
     sensColor=3;

  }
   if(redColor > greenColor && redColor > blueColor){
      sensColor=2;
 
  }
  if(((inRange(redFrequency, blueFrequency-35, greenFrequency+35)|| inRange(redFrequency, greenFrequency-35, blueFrequency+35))&& ((inRange(blueFrequency,redFrequency-20, greenFrequency+20) ||inRange(blueFrequency,greenFrequency-20,redFrequency-20))) && ((inRange(greenFrequency, blueFrequency-20, redFrequency+20) || inRange(greenFrequency, redFrequency-20, blueFrequency+20)))))
  { 
  
    sensColor=1;
  }
  
  if(blueColor > redColor && blueColor > greenColor ){
    sensColor=4;
  
  }
  
  

  
    if(l1==sensColor)
    {
      currentTime = millis(); 
      while(millis()-currentTime <4000){
        st.step(-150);
      }
      st.step(0);
      servo1.write(30);
      delay(3000);
      servo1.write(73);
      l1=-1;

      if(ride== true){
        st.step(steps);
      }
    }
    if(l2==sensColor)
    {
      currentTime = millis(); 
      while(millis()-currentTime <4000){
        st.step(-150);
      }

      st.step(0);
      servo1.write(30);
      delay(3000);
      servo1.write(73);
      l2=-1;
      if(ride== true){
        st.step(steps);
      }
    }
    if(r1==sensColor)
    {
      currentTime = millis(); 
      while(millis()-currentTime <4000){
        st.step(-150);
      }
      st.step(0);
      servo1.write(180);
      delay(3000);
      servo1.write(73);
      r1=-1;
      if(ride== true){
        st.step(steps);
      }
      
    }
    if(r2==sensColor)
    {
     
     currentTime = millis(); 
      while(millis()-currentTime <4000){
        st.step(-150);
      }

      servo1.write(180);
      delay(3000);
      servo1.write(73);
      r2=-1;
      if(ride== true){
        st.step(steps);
      }

    }


 
   
    
    
   
}
