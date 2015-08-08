int amegaPinsArray[16];
int endofLineRPin = 0;
int endofLineLPin = 1;

int leftMax;
int rightMax;
int onRight = true;
int onLeft = true;

int arrayNum = 14;

void setup() {
  Serial.begin(9600);
  leftMax = 450;
  rightMax = 450;

  
  int amegaPinsArrayTemp[16] = {
    37,35,33,31, 29,27,25,23, 22,24,26,28, 30,32,34,36  
    //22,24,26,28, 30,32,34,36,  37,35,33,31, 29,27,25,23    
  };                                      
  // put your setup code here, to run once:
  for(int i=0; i<16; i++){
    amegaPinsArray[i] = amegaPinsArrayTemp[i];
    pinMode(amegaPinsArray[i], OUTPUT);
    digitalWrite(amegaPinsArray[i], LOW);
  }
Serial.println("Setup Done");
}


void loop() {
int  valueEndLineLeft  = analogRead(endofLineLPin);
int  valueEndLineRight = analogRead(endofLineRPin);
  //Serial.println(valueEndLineLeft);
  //Serial.println(valueEndLineRight);
  //delay(10);
  ///*
   if(valueEndLineLeft > leftMax){ 
      if(onLeft) {
        delay(500);
        Serial.print("LEFT: ");
        Serial.println(arrayNum);
        onLeft = false;
        onRight = true;
        
        for(int i = 0; i < 16; i++) {
          digitalWrite(amegaPinsArray[i], LOW);
          digitalWrite(amegaPinsArray[arrayNum], HIGH);
        }
        
        arrayNum++;
        arrayNum%=16;
        
      }
    }

    if(valueEndLineRight > rightMax){
      if(onRight) {
        delay(500);
        Serial.print("RIGHT: ");
        Serial.println(arrayNum);
        onRight = false;
        onLeft = true;
        
        for(int i = 0; i < 16; i++) {
          digitalWrite(amegaPinsArray[i], LOW);
          digitalWrite(amegaPinsArray[arrayNum], HIGH);
        } 
        arrayNum++;
        arrayNum%=16;
        
      }
    }
}

