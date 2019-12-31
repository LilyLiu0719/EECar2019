// TODO: Write the functions from what you learned in former labs.

#include  <SoftwareSerial.h>
#include <Wire.h>  
#define DEBUG

/**************************************/
/*   Function Prototypes Define Here  */
/*   Finish TODO in Blacking Function */
/**************************************/
void Tracing_Mode();
void MotorWriting(double vR, double vL);
void MotorInverter(int motor, bool& dir);
void Send_OK();

/***************************/
/*   Functions Definition  */
/***************************/

//TODO
void Tracing_Mode() {
   //TODO
   // Simple Tracking
   /*************************************************/
   /* Read the sensor value and determine wether to */
   /* turn left or turn right or go straight        */
   /*************************************************/
   int l2=digitalRead(L2);
   int l1=digitalRead(L1);
   int m=digitalRead(M);
   int r1=digitalRead(R1);
   int r2=digitalRead(R2);
      
//   Serial.println("l2");
//   Serial.println(l2);
//   Serial.println("l1");
//   Serial.println(l1);
//   Serial.println("m");
//   Serial.println(m);
//   Serial.println("r1");
//   Serial.println(r1);
//   Serial.println("r2");

   double _Tp=75;
   double _w2=200;
   double _w1=80;
   double _Kp;

   double vR;
   double vL;

   vL=_w2*(r1+r2)/2-(_w2*(l1+l2)/2)+_Tp+30;
   vR=_w2*(l1+l2)/2-(_w2*(r1+r2)/2)+_Tp-30;
//   vL = 200;
//   vR = 200;
  
   MotorWriting(vR,vL);
}

//TODO
void MotorWriting(double vR, double vL) {
  if(vR>=0){
    if(R_dir)analogWrite(MotorR_PWMR,vR);
    else {
      MotorInverter(MotorR_PWMR,R_dir);
      analogWrite(MotorR_PWMR,vR);
    }
  }
  else if(vR<0){
    if(!R_dir){
      Serial.println("R_dir = false");
      analogWrite(MotorR_PWMR,-vR);
    }
    else {
      Serial.println("R_dir = true");
      MotorInverter(MotorR_PWMR,R_dir);
      analogWrite(MotorR_PWMR,-vR);
    }
  }
    
 if(vL>=0){
    if(L_dir)analogWrite(MotorL_PWML,vL);
    else {
      MotorInverter(MotorL_PWML,L_dir);
      analogWrite(MotorL_PWML,vL);
    }
  }
  else if(vL<0){
    if(!L_dir)analogWrite(MotorL_PWML,-vL);
    else {   
      MotorInverter(MotorL_PWML,L_dir);
      analogWrite(MotorL_PWML,-vL);
    }
  }
}
//TODO
void MotorInverter(int motor, bool& dir) {
   //TODO
   /*************************************/
   /* Reverse the dir for the given dir */
   /* value and motor(Left or Right)    */
   /*************************************/
   if(motor == MotorL_PWML)
   {
    if(dir)
    {
      digitalWrite(MotorL_I3,LOW);
      digitalWrite(MotorL_I4,HIGH);
      dir=false;
      }
    else
    {
      digitalWrite(MotorL_I3,HIGH);
      digitalWrite(MotorL_I4,LOW);
      dir=true;
      }
    }

    if(motor == MotorR_PWMR)
   {
    if(dir)
    {
      digitalWrite(MotorR_I1,LOW);
      digitalWrite(MotorR_I2,HIGH);
      dir=false;
      }
    else
    {
      digitalWrite(MotorR_I1,HIGH);
      digitalWrite(MotorR_I2,LOW);
      dir=true;
      }
    }
}
//
//void Send_OK() {
//   I2CBT.write('O');
//}
