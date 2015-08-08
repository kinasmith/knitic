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
  1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
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
  //int ledArray[16];
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
    // int ledArrayTemp[totalArrayFromSelenoids] =       {38,40,42,44,46,48,50,52,5,6,43,45,47,49,51,7};
    int amegaPinsArrayTemp[totalArrayFromSelenoids] = {
      37,35,33,31, 29,27,25,23, 22,24,26,28, 30,32,34,36  //this one is right...I think.
      //22,24,26,28, 30,32,34,36,  37,35,33,31, 29,27,25,23
      //23,25,27,29, 31,33,35,37,  36,34,32,30, 28,26,24,22
      //37,36,35,34, 33,32,31,30,  29,28,27,26, 25,24,23,22
      //36,34,32,30, 28,26,24,22,  23,25,27,29, 31,33,35,37
      //37,35,33,31, 29,27,25,23,   22,24,26,28, 30,32,34,36
    };
    for(int i=0; i<16; i++){
      amegaPinsArray[i] = amegaPinsArrayTemp[i];
     // ledArray[i] = ledArrayTemp[i];
      pinMode(amegaPinsArrayTemp[i], OUTPUT);
     // pinMode(ledArrayTemp[i], OUTPUT);
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
    if(myEncoders->lastStitch != myEncoders->stitch){
      myEncoders->lastStitch = myEncoders->stitch;
      Serial.println(myEncoders->stitch);
      //if the stitch Changes
      // RIGHT direction 
      if(myEncoders -> headDirection == -1){
        int pos = myEncoders -> encoder1Pos; //get the position
        //if position is greater than 15
        if(pos > 15){ 
          // int i = abs(pos-8)%16; 
          int i = abs(pos)%16; 
          if(myEndlines->phase == 0){
             // i = abs(pos-8)%16; // maybe +8
            i = abs(pos)%16; // maybe +8
          }else{
            // validated
            i = abs(pos)%16;
          }
          currentStitchSetup = pos-16;
          currentSolenoidIDSetup = i;
          Serial.print("curr. stitch: "); Serial.println(currentStitchSetup);
          Serial.print("curr. Solenoid ID: "); Serial.println(currentSolenoidIDSetup);

          if(currentStitchSetup>=0 && currentStitchSetup<254){
            currentPixState = pixelBin[currentStitchSetup];
            if(solenoidstateOn[i] != (currentPixState==1) ){
              digitalWrite(amegaPinsArray[i], currentPixState);
              // digitalWrite(ledArray[i], currentPixState);  
              solenoidstateOn[i] = (currentPixState==1);
            }
          }
        }
      }
      // LEFT direction
      else if(myEncoders->headDirection==1 ){
        int pos = myEncoders->encoder1Pos;
        if(pos < 256-8 ){
          int i;
          if(myEndlines->phase==0){
            // validated
            i = abs(pos)%16;// was 0, means no +8
          }else{
            //i = abs(pos-8)%16;// -8
            i = abs(pos)%16; // maybe +8
          }
          currentStitchSetup = pos-40; 
          currentSolenoidIDSetup = i;
          
          Serial.print("curr. stitch: "); Serial.println(currentStitchSetup);
          Serial.print("curr. Solenoid ID: "); Serial.println(currentSolenoidIDSetup);


          if(currentStitchSetup>=0 && currentStitchSetup<254){
            currentPixState = pixelBin[currentStitchSetup];
            if( solenoidstateOn[i] !=(currentPixState==1) ){
              digitalWrite(amegaPinsArray[i], currentPixState);
              //digitalWrite(ledArray[i], currentPixState);   
              solenoidstateOn[i] = (currentPixState==1);
            }
          }
        }
      }
      // Set all solenoids OFF when end of line
      if(myEncoders->encoder1Pos==0 || myEncoders->encoder1Pos==255  ){
        for(int i=0;i<16;i++){
          digitalWrite(amegaPinsArray[i], LOW);
          //digitalWrite(ledArray[i], LOW);
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

  void ifChanged(){
    if(changed){
      changed = false;
#ifdef arduinoTypeDUE
      setArduinoMegaPins();
#endif
    }
  }

#ifdef arduinoTypeDUE
  /*
  boolean isCurrentSolenoid(int i,int r){
    int stitch = myEncoders->stitch;
    int headDirection = -myEncoders->headDirection;
    return (  (stitch<=176 && stitch>=-24 && headDirection==-1) && ((stitch-2+(i*headDirection))%16)==r );//|| ( (stitch>=24 && stitch<=224 &&  headDirection==1)  && ((stitch+8-(i*headDirection))%16)==r );
  }
*/
  void setArduinoMegaPins(){
    for(int i=0;i<16;i++) { 
      /*isCurrentSolenoid(i,7) myEncoders->headDirection==1 && myEncoders->stitch==25 && i==0  && */ 
      if(solenoidstate[i]==true ) {
        if(solenoidstateOn[i]==false) {
          digitalWrite(amegaPinsArray[i], HIGH);
          //digitalWrite(ledArray[i], HIGH);
          solenoidstateOn[i] = true;
          ////Serial.print(myEncoders->stitch);//Serial.print("::");//Serial.print(i);//Serial.println("::set ON solenoid");
        }
      }
      else if(solenoidstateOn[i]==true) {
        digitalWrite(amegaPinsArray[i], LOW);
        //digitalWrite(ledArray[i], LOW);
        solenoidstateOn[i] = false;
        ////Serial.print(myEncoders->stitch);//Serial.print("::");//Serial.print(i);//Serial.println("::set OFF solenoid");
      }
    }
  }
#endif

};
#endif



















