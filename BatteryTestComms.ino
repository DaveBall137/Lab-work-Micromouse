  #include <SoftwareSerial.h>
  SoftwareSerial HC12(12,13); //12,13 for Arduino Mega Tx, Rx
 
  int FR = 50; //setting pin 50 to the Front Right sensor
  int FL = 51; //setting pin 51 to the Front Left sensor
  int BL = 52; //setting pin 52 to the Back Left sensor
  int BR = 53; //setting pin 53 to the Back Right sensor

  int FRBumpPower = 40; // Supplying power to common
  int FRBump = 41; // Gives 5V when pressed
  int FLBumpPower = 42; //...
  int FLBump = 43; //...
  int BumpGND = 45; // Grounds the bumpers pull down resistors

  int ENA = 10; //Setting pin 2 as a PWM for A changed to 10
  int IN1 = 49; //Setting pin 49 for the MC pin 1
  int IN2 = 48; //Setting pin 48 for the MC pin 2
  int IN3 = 47; //Setting pin 47 for the MC pin 3
  int IN4 = 46; //Setting pin 46 for the MC pin 4
  int ENB = 11; //Setting pin 3 as a PWM for B changed to 11
  int MOTORA;
  int MOTORB;
  int MotorGND = 44;

  int tachA = 2; // changed from 10 -> 2
  int tachB = 3; // changed from 11 -> 3

  unsigned long tachATime = 0;
  unsigned long tachATime1 = 0;
  int DifferenceA = 0;
  unsigned long tachBTime = 0;
  unsigned long tachBTime1 = 0;
  int DifferenceB = 0;

  int RWL = A0; //setting pin White line middle to pin 24
  int MWL = A1; //setting pin White line middle to pin 24
  int LWL = A2; //setting pin White line middle to pin 24
  int PWL = 23;
  int ZWL = 22;
  int LeftWhite;
  int MiddleWhite;
  int RightWhite;
  int LeftBlack;
  int MiddleBlack;
  int RightBlack;
  int ThresholdComplete; 
  int LeftTest = 0;
  int MiddleTest = 0;
  int RightTest = 0;
  float ThreshL;
  float ThreshM;
  float ThreshR;

  int Distance = 0;
  int BackDistance = 5;
  int ForwardDistance = 5;
  int RightDistance = 3;
  int LeftDistance = 3;

  float voltage = 0;
  float threshold = 6.2; //Threshold depending on the battery to determine low battery SoC
  float v_read = A3;
  float Adjustment = -0.090;
  float voltage1 =0;
  float voltage2 =0;
  float voltage3 =0;
  float voltage4 =0;
  float voltage5 =0;
  float voltage6 =0;
  float voltage7 =0;
  float voltage8 =0;
  float voltage9 =0;
  float voltage10 =0;

  void setup() {
  // put your setup code here, to run once:
  pinMode(PWL, OUTPUT);
  pinMode(ZWL, OUTPUT);
  digitalWrite(PWL, LOW);
  digitalWrite(ZWL, LOW);
  pinMode(BR, INPUT);
  pinMode(BL, INPUT);
  pinMode(FR, INPUT);
  pinMode(FL, INPUT);

  pinMode(v_read,INPUT);

  pinMode(FLBump,INPUT);
  pinMode(FRBump, INPUT);
  pinMode(FRBumpPower, OUTPUT);
  pinMode(FLBumpPower,OUTPUT);
  pinMode(BumpGND,OUTPUT);
  digitalWrite(FRBumpPower,HIGH);
  digitalWrite(FLBumpPower,HIGH);
  digitalWrite(BumpGND,LOW);

  Serial.begin(9600);
  HC12.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MotorGND, OUTPUT);
  digitalWrite(MotorGND, LOW);
  pinMode(tachA,INPUT);
  pinMode(tachB,INPUT);

  LeftWhite = 0;
  MiddleWhite = 0;
  RightWhite = 0;
  LeftBlack = 0;
  MiddleBlack = 0;
  RightBlack = 0;
  LeftTest = 0;
  MiddleTest = 0;
  RightTest = 0;
  ThresholdComplete = 0;
  int ThreshL = 0;
  int ThreshM = 0;
  int ThreshR = 0;

  pinMode(tachA, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(tachA),countA,RISING);
  pinMode(tachB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(tachB),countB,RISING);
  MOTORA = 200;
  MOTORB = 185; // tested at this speed, if the speed was too high it can be tested again
  }

void forward(){
  while(Distance > 0){
    analogWrite(ENA, MOTORB);
    analogWrite(ENB, MOTORA);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Forward");
    comparison();
    Distance--;
    //Serial.print("Distance for travel ");
    //Serial.println(Distance);
  }
}
void back() {
  while(Distance > 0){
    analogWrite(ENA, MOTORA);
    analogWrite(ENB, MOTORB);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Back");
    Distance--;
    //Serial.print("Distance for travel ");
    //Serial.println(Distance);
  }
}

void right() {
  while(Distance > 0){
    analogWrite(ENA, MOTORA);
    analogWrite(ENB, MOTORB);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Right");
    Distance--;
    //Serial.print("Distance for travel ");
    //Serial.println(Distance);
  }
}

void left() {
  while(Distance > 0){
    analogWrite(ENA, MOTORA);
    analogWrite(ENB, MOTORB);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Left");
    Distance--;
    //Serial.print("Distance for travel ");
    //Serial.println(Distance);
  }
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
}

void comparison(){
  if((DifferenceA > -750) && (DifferenceA > -750)){
    /*Serial.print("Difference is: ");
    Serial.println((DifferenceA - DifferenceB));
    Serial.print("This is MOTORA: ");
    Serial.println(MOTORA);
    Serial.print("This is MOTORB: ");
    Serial.println(MOTORB);*/
    if((DifferenceA > DifferenceB) && (MOTORB >= 150)){
      MOTORB--;
    }
    else if((DifferenceA < DifferenceB) && (MOTORB < 250)){
      MOTORB++;
      }
    else if((DifferenceA < DifferenceB) && (MOTORB >= 250 )){
        MOTORB -= 10;
      }
    else if(MOTORB < 150 ){
        MOTORA == 0;
        MOTORB == 0;
      }  
    else{
      //Serial.println("SYNCHED");
      }
      }
      else{

      }
}

void countA() {
  tachATime = micros();
  DifferenceA = tachATime - tachATime1;
  tachATime1 = tachATime;
  //Serial.print("DifferenceA :");
  //Serial.println(DifferenceA); 
}

void countB() {
  tachBTime = micros();
  DifferenceB = tachBTime - tachBTime1;
  tachBTime1 = tachBTime;
  //Serial.print("DifferenceB :");
  //Serial.println(DifferenceB);  
}
void VoltageRead(){
    /*Serial.print("Read Voltage:"); //Prints to monitor
    Serial.println(ReadVoltage); // Only needed for testing*/
    voltage1 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage2 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage3 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage4 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage5 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage6 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage7 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage8 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage9 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage10 =((analogRead(v_read)*(7.5/1023))- Adjustment);
    delay(2);
    voltage = ((voltage1 + voltage2 + voltage3 + voltage4 + voltage5 + voltage6 + voltage7 + voltage8 + voltage9 + voltage10)/10);
    //voltage = ((analogRead(v_read)*(7.5/1023))- Adjustment);

    
    //voltage = analogRead(v_read);
    //Serial.print("Voltage:"); //Prints to monitor
    //Serial.println(voltage);
    HC12.print("Voltage:"); //Prints to HC-12 Module
    HC12.println(voltage);//Prints to HC-12 Module
  while(voltage < threshold){
      Serial.print("Voltage is too low:"); //Prints to monitor
      Serial.println(voltage);

      HC12.print("Voltage is too low:"); //Prints to HC-12 Module
      HC12.println(voltage);//Prints to HC-12 Module
      stop();
      Serial.print("NEED TO RETURN HOME");
      HC12.print("NEED TO RETURN HOME"); //Prints to HC-12 Module
      voltage = ((analogRead(v_read)*(7.5/1023))- Adjustment);
    }
}

void obstacleavoidance(){
  VoltageRead();
  /*if((digitalRead(FR)==HIGH) && (digitalRead(FL)==HIGH)){
    Serial.println("FRONT DETECT");
    //HC12.println("FRONT DETECT");
    //communication();
    stop();
    Distance = RightDistance;
    right();
    }
    else if((digitalRead(FR)==HIGH) && (digitalRead(FL)==LOW)){
      Serial.println("Front Right Active - STOP");
      //HC12.println("Front Right Active - STOP");
      //communication();
      stop();
      Distance = LeftDistance;
      left(); 
    }
    else if((digitalRead(FR)==LOW) && (digitalRead(FL)==HIGH)){
      Serial.println("Front Left Active - STOP");
      //HC12.println("Front Left Active - STOP"); // Commented out to reduce sent information
      //communication();
      stop();
      Distance = RightDistance;
      right();
    }
    else if((digitalRead(FRBump)==HIGH) && (digitalRead(FLBump)==HIGH)){
      Serial.println("FRONT Bumpers DETECT");
      //HC12.println("FRONT Bumpers DETECT");
      //communication();
      stop();
      Distance = BackDistance;
      back();
      Distance = RightDistance;
      right();
    }
    else if((digitalRead(FRBump)==HIGH) && (digitalRead(FLBump)==LOW)){
      Serial.println("Front Right Bumper - STOP");
      //HC12.println("Front Right Bumper - STOP");
      //communication();
      stop();
      Distance = BackDistance;
      back();
      Distance = LeftDistance;
      left();
    }
    else if((digitalRead(FRBump)==LOW) && (digitalRead(FLBump)==HIGH)){
      Serial.println("Front Left Bumper - STOP");
      //HC12.println("Front Left Bumper - STOP");
      //communication();
      stop();
      Distance = BackDistance;
      back();
      Distance = RightDistance;
      right();
      }
    else{
      Distance = ForwardDistance;
      forward();
      }*/
      
}

void communication(){
  if(HC12.available()){ // if HC-12 module has data
    Serial.write(HC12.read()); // sends data from HC12 to Serial monitor
  }
  
  if(Serial.available()){ // if Serial monitor has data
    HC12.write(Serial.read()); // sends data from arduino to HC12 module which will transmit
  }
}


void loop() {
  // put your main code here, to run repeatedly:
      obstacleavoidance();
}
