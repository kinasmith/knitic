#ifndef ENDLINES_H_
#define ENDLINES_H_

#include "arduino.h"
#include "sound_alerts.h"

class endLines{
private:
  soundAlerts* mySoundAlerts; //Pointer for soundAlert....Array?
  // analog arduino pin
  int endLineLeftAPin; //endline LEFT Analog Pin
  int endLineRightAPin; //endline RIGHT Analog Pin
  encoders* myEncoders;
  int filterValueLeftMin;
  int filterValueRightMin;
  int filterValueLeftMax;
  int filterValueRightMax;
  int maxLeft;
  int maxRight;

public:
  int valueEndLineLeft;
  int valueEndLineRight;
  int phase; //phase is what side of the machine it's on?...
  //
  endLines(){
  }
  ~endLines(){
  }

  void setup(){
    maxLeft = 0;
    maxRight= 0;
    endLineLeftAPin = 1;
    endLineRightAPin = 0;
    //setup trigger levels for the switch
    filterValueLeftMin = 10; 
    filterValueRightMin = 10;
    filterValueLeftMax = 460;
    filterValueRightMax = 460;
  }

  void setPosition(encoders* _myEncoders, soundAlerts* _mySoundAlerts){
    myEncoders = _myEncoders;
    mySoundAlerts = _mySoundAlerts;
  }

  void loop(){
    // -1 is moving from left to RIGHT
    // 1 is moving from right to LEFT
    // Left end of line - looking change phase
    if( myEncoders->headDirection == -1){
      valueEndLineLeft  = analogRead(endLineLeftAPin);
      if( valueEndLineLeft < filterValueLeftMin || analogRead(endLineLeftAPin) > filterValueLeftMax){ 
        if(myEncoders->_8segmentEncoder){
          phase = 1;
        }
        else{
          phase = 0;
        }
      }
    }
    // Right end of line - looking change phase
    if( myEncoders->headDirection==1){ 
      valueEndLineRight = analogRead(endLineRightAPin);
      if( valueEndLineRight <filterValueRightMin || analogRead(endLineRightAPin) >filterValueRightMax){
        if(myEncoders->_8segmentEncoder){
          phase = 1;
        }
        else{
          phase = 0;
        }
      }
    }
  }

};
#endif

