//---------------------------------------------------------------------------------
// SOLENOIDS
//---------------------------------------------------------------------------------
// Controled by Toshiva

#ifndef SOLENOIDS_H_
#define SOLENOIDS_H_

#include "arduino.h"
#include "encoders.h"
#include "endLines.h"

int pixelBin[256] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

class solenoids{
private:
  encoders* myEncoders;
  endLines* myEndlines;
  byte myDataOut;
#ifdef arduinoTypeDUE
  int amegaPinsArray[16];
#endif
public:
  int currentPixState;
  int currentStitchSetup;
  int currentSolenoidIDSetup;
  boolean changed;
  boolean solenoidstate[16];
  boolean solenoidstateOn[16];
  String _16solenoids;
  boolean sectionPosition;
  solenoids(){
#ifdef arduinoTypeDUE  
    int amegaPinsArrayTemp[totalArrayFromSelenoids] = {
      37,35,33,31, 29,27,25,23, 22,24,26,28, 30,32,34,36  //this one is right...I think.
    };
    for(int i=0; i<16; i++){
      amegaPinsArray[i] = amegaPinsArrayTemp[i];
      pinMode(amegaPinsArrayTemp[i], OUTPUT);
    }
#endif
  }

  ~solenoids(){
  }

  void setup(endLines* _myEndlines,encoders* _myEncoders){
    sectionPosition = false;
    myEndlines = _myEndlines;
    myEncoders = _myEncoders;
    _16solenoids = "0000000000000000";
    changed = false;
#ifdef arduinoTypeDUE
    for(int i=0;i<16;i++){
      solenoidstate[i] = (_16solenoids[i] != '0');
      solenoidstateOn[i] = (_16solenoids[i] != '0');
    }
#endif
  }

  void loop(){
    //if the stitch Changes
    if(myEncoders->lastStitch != myEncoders->stitch){
      myEncoders->lastStitch = myEncoders->stitch;

      Serial.println(myEncoders->stitch);

      // RIGHT direction 
      if(myEncoders -> headDirection == -1){
        Serial.print("Moving Right: "); //Serial.print("phase: "); Serial.println(myEndlines->phase);
        //int pos = (myEncoders -> encoder1Pos); //get the position
        int pos = myEncoders -> stitch;
        // if(pos > 15){ 
        if(pos >= 0 && pos <= 200){ 
           //int i = abs(pos-8)%16; 
          int i = abs(pos)%16; 
         // if(myEndlines->phase == 0){ // Phase = 0 is Carriage was On Left side
           //i = abs(pos-8)%16; // maybe +8
            i = abs(pos) % 16; // maybe +8
         // }else{
            // validated --WHy is this here?
          //  i = abs(pos)%16;
         // }
          currentStitchSetup = pos; //pos-16
          currentSolenoidIDSetup = i;

          Serial.print("curr. stitch: "); Serial.println(currentStitchSetup);
          Serial.print("curr. Solenoid ID: "); Serial.println(currentSolenoidIDSetup);

              //WHAT IS THIS?
          if(currentStitchSetup >= 0 && currentStitchSetup < 200){ //IF the head is within the switches....no. 200 is the left switch
            
            currentPixState = pixelBin[currentStitchSetup]; //Pixel Bin is an array of 256 values. It pulls values from the Serial Port
           
            if(solenoidstateOn[i] != (currentPixState == 1) ){ //if the current solenoid is different from the pixelBin value
              Serial.print("switching ");Serial.print(amegaPinsArray[i]);Serial.print(": ");Serial.println(currentPixState);
              digitalWrite(amegaPinsArray[i], currentPixState); //the that state to the Indexed Solenoid
              solenoidstateOn[i] = (currentPixState==1); //update array of current solenoid States
            }
          }
        }
      }
      // LEFT direction
      else if(myEncoders->headDirection == 1){
        Serial.print("Moving Left: "); //Serial.print("phase: "); Serial.println(myEndlines->phase);
        //int pos = myEncoders->encoder1Pos;
        int pos = myEncoders -> stitch;
        // if(pos < 256-8 ){
        if(pos <= 200 && pos >= 0){
         // int i;
         // if(myEndlines->phase == 0){ //Carriage Phase == 0 means it was on LEFT Side
            // validated
           int i = abs(pos)%16;// was 0, means no +8
        //  }else{
          //  i = abs(pos-8)%16;// -8
            //i = abs(pos)%16; // maybe +8
         // }
          currentStitchSetup = pos; //pos-40
          currentSolenoidIDSetup = i;
          
          Serial.print("curr. stitch: "); Serial.println(currentStitchSetup);
          Serial.print("curr. Solenoid ID: "); Serial.println(currentSolenoidIDSetup);


          if(currentStitchSetup >= 0 && currentStitchSetup < 200){
            currentPixState = pixelBin[currentStitchSetup];
            if( solenoidstateOn[i] !=(currentPixState==1) ){
              Serial.print("switching ");Serial.print(amegaPinsArray[i]);Serial.print(": ");Serial.println(currentPixState);
              digitalWrite(amegaPinsArray[i], currentPixState);
              solenoidstateOn[i] = (currentPixState==1);
            }
          }
        }
      }
      // Set all solenoids OFF when end of line
      if(myEncoders->encoder1Pos < 0 || myEncoders->encoder1Pos > 200  ){
        for(int i=0;i<16;i++){
          digitalWrite(amegaPinsArray[i], LOW);
          solenoidstateOn[i] = false; 
        }
      }
      /*
      if(myEncoders->encoder1Pos<=1 || myEncoders->encoder1Pos>254  ){
        
        if(myEncoders->last_8segmentEncoder != myEncoders->_8segmentEncoder){
          sectionPosition = 0; 
        }else{
          sectionPosition = 1;
        }
      }
      */
    }
    /*
#ifdef arduinoTypeDUE
     if( myEncoders->lastStitch!=myEncoders->stitch){
     myEncoders->lastStitch=myEncoders->stitch;
     setArduinoMegaPins();
     if(changed){ 
     changed = false;
     }
     }
     #endif
     */
  }
/*
  void ifChanged(){
    if(changed){
      changed = false;
#ifdef arduinoTypeDUE
      setArduinoMegaPins();
#endif
    }
  }
*/
// #ifdef arduinoTypeDUE
  /*
  boolean isCurrentSolenoid(int i,int r){
    int stitch = myEncoders->stitch;
    int headDirection = -myEncoders->headDirection;
    return (  (stitch<=176 && stitch>=-24 && headDirection==-1) && ((stitch-2+(i*headDirection))%16)==r );//|| ( (stitch>=24 && stitch<=224 &&  headDirection==1)  && ((stitch+8-(i*headDirection))%16)==r );
  }
*/
//   void setArduinoMegaPins(){
//     for(int i=0;i<16;i++) { 
//       /*isCurrentSolenoid(i,7) myEncoders->headDirection==1 && myEncoders->stitch==25 && i==0  && */ 
//       if(solenoidstate[i]==true ) {
//         if(solenoidstateOn[i]==false) {
//           digitalWrite(amegaPinsArray[i], HIGH);
//           //digitalWrite(ledArray[i], HIGH);
//           solenoidstateOn[i] = true;
//           ////Serial.print(myEncoders->stitch);//Serial.print("::");//Serial.print(i);//Serial.println("::set ON solenoid");
//         }
//       }
//       else if(solenoidstateOn[i]==true) {
//         digitalWrite(amegaPinsArray[i], LOW);
//         //digitalWrite(ledArray[i], LOW);
//         solenoidstateOn[i] = false;
//         ////Serial.print(myEncoders->stitch);//Serial.print("::");//Serial.print(i);//Serial.println("::set OFF solenoid");
//       }
//     }
//   }
// #endif

 };
 #endif



















