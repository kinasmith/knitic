//Test of 
//255 pulses across the bed of the machine

int signalPin1 = 2;
int signalPin2 = 3;
int signalPin3 = 4;
int val1, val2, val3;
int l_val1 = 0;
int l_val2 = 0;
int l_val3 = 0;
int A_cnt = 0;
int B_cnt = 0;
int C_cnt = 0;

void setup()
{
 // pinMode(signalPin1, INPUT);
 // pinMode(signalPin2, INPUT);
 // pinMode(signalPin3, INPUT);
  attachInterrupt(2, cnt_A, RISING);
  attachInterrupt(3, cnt_B, RISING);
  attachInterrupt(4, cnt_C, RISING);
  Serial.begin(9600);
}

void cnt_A(){
 A_cnt++; 
 //Serial.print("A:");
 //Serial.println(val1);
}

void cnt_B() {
  B_cnt++;
  //Serial.print("B:");
  //Serial.println(val2);
}

void cnt_C() {
  C_cnt++;
  /*
  Serial.print("C:");
  Serial.println(val3);
  Serial.print(": ");
  Serial.print(A_cnt);
  Serial.print(" : ");
  Serial.print(B_cnt);
  Serial.print(" : ");
  Serial.print(C_cnt);
  Serial.println();
  */
}
  

void loop(){
  Serial.print(A_cnt);
  Serial.print(" : ");
  Serial.print(B_cnt);
  Serial.print(" : ");
  Serial.print(C_cnt);
  Serial.println();
  /*
  val1 = digitalRead(signalPin1);
  val2 = digitalRead(signalPin2);
  val3 = digitalRead(signalPin3);
  if(val1 != l_val1){
    if(val1 == 1) {
      A_cnt++;
      Serial.print("A:");
      Serial.println(val1);
    }
    l_val1 = val1;
  }
  if(val2 != l_val2){
    if(val2 == 1) {
      B_cnt++;
      Serial.print("B:");
      Serial.println(val2);
    }
    l_val2 = val2;
  }
  if(val3 != l_val3){
    if(val3 == 1) {
      C_cnt++;
      Serial.print("C:");
      Serial.println(val3);
      Serial.print(": ");
      Serial.print(A_cnt);
      Serial.print(" : ");
      Serial.print(B_cnt);
      Serial.print(" : ");
      Serial.print(C_cnt);
      Serial.println();
    }
    l_val3 = val3;

  }
  */
}
