//Test of 

int signalPin1 = 2;
int signalPin2 = 3;
int signalPin3 = 4;
int val1, val2, val3;
int l_val1 = 0;
int l_val2 = 0;
int l_val3 = 0;

void setup()
{
  pinMode(signalPin1, INPUT);
  pinMode(signalPin2, INPUT);
  pinMode(signalPin3, INPUT);
  Serial.begin(9600);
}

void loop(){
  val1 = digitalRead(signalPin1);
  val2 = digitalRead(signalPin2);
  val3 = digitalRead(signalPin3);
  
  if(val1 != l_val1){
    Serial.println("A:ON");
  }else{
    Serial.println("A:OFF");
  }
  
  if(digitalRead(signalPin2)){
    Serial.println("B:ON");
  }else{
    Serial.println("B:OFF");
  }
  
  if(digitalRead(signalPin3)){
    Serial.println("C:ON");
  }else{
    Serial.println("C:OFF");
  }
  
}
