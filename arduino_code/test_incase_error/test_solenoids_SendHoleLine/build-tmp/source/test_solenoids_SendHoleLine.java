import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class test_solenoids_SendHoleLine extends PApplet {



int[] pixelReceived = {
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
  0,0,0,0,0,0,0,0
};

int[] pixelSend = {
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
  0,0,0,0,0,0,0,0
};

int[] pixelLine1 = {
  1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
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
  0,0,0,0,0,0,0,0
};

int[] pixelLine2 = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1
};

byte lf = 0x40; // @ 
byte footer = 126; // 
byte startChar = 4; // end of transmission 
Serial myPort;
String myString;

int stitch;
boolean endLineStarted;
int headDirection;
String statusMachine;

int h_window = 10;
int w_window = (h_window/2)*200;

public void setup(){
  size(w_window, h_window);
  //String portName = Serial.list()[2];
 // println(portName);
 // myPort = new Serial(this, portName,115200);
 // myPort.clear();
}

public void draw(){
  for (int i=0; i<200; i++) {
    if (pixelSend[i] == 0) {
      fill(0, 0, 255);
    } else {
      fill(255, 255, 255);
    }
    rect(i*height/2, 0, height/2, height/2);
  }
  for (int i=0; i<200; i++) {
    if (pixelReceived[i]==0) {
      fill(100, 0, 255);
    } else {
      fill(255, 255, 255);
    }
    rect(i*height/2, height/2, height/2, height/2);
  }
 // receiveSerial();
}

/*
void chechBetweenSendAndReceived(){
  for (int i=0; i<200; i++) {
    if(pixelSend[i] != pixelReceived[i] ){
      sendtoKnittingMachine();
      break;
    }
  }
}

void receiveSerial() {
  try {
    int timeStart = millis();
    //serialAvailableBuffer = myPort.available();
    while (myPort!=null && myPort.available ()>0  && (millis()-timeStart<300 )) {
      println("Receive Serial___"+Integer.toString(myPort.available()));
      myString = myPort.readStringUntil(lf); //read string that Arduino is puking out
      // PIXELS stored now in arduino
      try {
        if (myString != null && myString.length()>200) {
          println("received:"+myString);
          for (int i=0; i<200; i++) {
            if (myString.substring(i, i+1).equals("0")) {
              pixelReceived[i] = 0;
            }
            else {
              pixelReceived[i] = 1;
            }
          }
          
          for (int i=0; i<200; i++) {
            if (pixelReceived[i]!=pixelSend[i]) {
              sendtoKnittingMachine();
              break;
            }
          }
        }
      }
      catch(Exception e) {
      }
      // Data sensors from arduino (encoders, endlines)
      if (myString != null && myString.length()<200) {
          println("received small:"+myString);
          String[] args = myString.split(",");
          if (args.length>2) {
            stitch = Integer.valueOf(args[0]);
            endLineStarted = !args[1].equals("0");
            headDirection = Integer.valueOf(args[2]);
            statusMachine = args[3];
          }
        }
    }
  }
  catch(Exception e) {
    println("ERROR in receive serial "+e.getMessage());
  }
}

void keyPressed(){
  if(key=='1'){ 
    sendtoKnittingMachine();
    for (int i=0;i<200;i++) {
      pixelSend[i] = pixelLine1[i];
    }
  }
  if(key=='2'){ 
    sendtoKnittingMachine();
    for (int i=0;i<200;i++) {
      pixelSend[i] = pixelLine2[i];
    }
  }
}
// send to arduino
void sendtoKnittingMachine() {
  println("send to machine");
  for (int i=0; i<200; i++) {
    myPort.write(pixelSend[i]);
  }
  myPort.write(footer);
}
*/
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "test_solenoids_SendHoleLine" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
