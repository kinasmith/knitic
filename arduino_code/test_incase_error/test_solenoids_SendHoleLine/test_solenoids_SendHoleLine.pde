import processing.serial.*;

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

void setup(){
  size(w_window, h_window);
  //String portName = Serial.list()[2];
 // println(portName);
 // myPort = new Serial(this, portName,115200);
 // myPort.clear();
}

void draw(){
  for (int i=0; i<200; i++) {
    if (pixelSend[i] == 0) {
      fill(0, 0, 255);
    } else {
      fill(255, 255, 255);
    }
    rect(i*height/2, 0, height/2, height/2);
  }
  for (int i=0; i<200; i++) {
    if (pixelReceived[i] == 0) {
      fill(100, 0, 255);
    } else {
      fill(255, 255, 255);
    }
    rect(i*height/2, height/2, height/2, height/2);
  }
 // receiveSerial();
}


void checkBetweenSendAndReceived(){
  for (int i=0; i<200; i++) {
    if(pixelSend[i] != pixelReceived[i] ){
      sendtoKnittingMachine();
      break;
    }
  }
}

void receiveSerial() {
  try {
    int timeStart = millis(); //What is this Start Time For?...waits for Serial to engage? 
    //serialAvailableBuffer = myPort.available(); //Why is this commented out?
    while (myPort != null && myPort.available () > 0 && (millis() - timeStart < 300 )) {
      println("Receive Serial___"+Integer.toString(myPort.available()));
      myString = myPort.readStringUntil(lf); //read string that Arduino is puking out
      // PIXELS stored now in arduino --> This doesn't mean anything?
      try {
        //If there is a string that is not empty and longer than 200
        
        if (myString != null && myString.length() > 200) {
          println("received:" + myString);
          for (int i = 0; i < 200; i++) {
            if (myString.substring(i, i+1).equals("0")) { //if any character..substring one character long == 0
              pixelReceived[i] = 0; //receive a 0
            }
            else { //otherwise
              pixelReceived[i] = 1; //receive a 1
            }
          }
            //This expects a string of JUST the data that was sent to the Arduino. Where is the sketch that goes with this?

          for (int i=0; i<200; i++) {
            if (pixelReceived[i] != pixelSend[i]) { //IF the received data == the sent data
              sendtoKnittingMachine(); //Send the data to the machine. 
              break;
            }
          }
        }
      }

      catch(Exception e) {
      }
      // Data sensors from arduino (encoders, endlines)
      if (myString != null && myString.length() < 200) {
          println("received small:"+myString);
          String[] args = myString.split(","); //makes an Array of strings split on the ','
          //pulls sensor values out of data string
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
