  int FR = 50; //setting pin 50 to the Front Right sensor
  int FL = 51; //setting pin 51 to the Front Left sensor
  int BL = 52; //setting pin 52 to the Back Left sensor
  int BR = 53; //setting pin 53 to the Back Right sensor
  
  int ENA = 10; //Setting pin 2 as a PWM for A changed to 10
  int IN1 = 49; //Setting pin 49 for the MC pin 1
  int IN2 = 48; //Setting pin 48 for the MC pin 2
  int IN3 = 47; //Setting pin 47 for the MC pin 3
  int IN4 = 46; //Setting pin 46 for the MC pin 4
  int ENB = 11; //Setting pin 3 as a PWM for B changed to 11
  int MOTORA;
  int MOTORB;
  
  int tachA = 3; // changed from 10 -> 3
  int tachB = 2; // changed from 11 -> 2
  
  int widthA;  int widthB;
  int MA1;  int MA2;  int MA3;  int MA4;  int MA5;  int MA6;  int MA7;  int MA8;  int MA9;  int MA10;  int MA11;  int MA12; 
  int MB1;  int MB2;  int MB3;  int MB4;  int MB5;  int MB6;  int MB7;  int MB8;  int MB9;  int MB10;  int MB11;  int MB12; 
  int AVwidthA;  int AVwidthB;
  
  
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
   

  
void setup() {
  // put your setup code here, to run once:
  pinMode(PWL, OUTPUT);
  pinMode(ZWL, OUTPUT);
  pinMode(BR, INPUT);
  pinMode(BL, INPUT);
  pinMode(FR, INPUT);
  pinMode(FL, INPUT);
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(tachA,INPUT);
  pinMode(tachB,INPUT);
  digitalWrite(PWL, HIGH);
  digitalWrite(ZWL, LOW);
  Serial.begin(9600);
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
  MOTORA = 200;
  MOTORB = 200; 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ThresholdComplete == 0){
    WhiteLineSensors();  
  }
  else{
    WhiteLineFollowing();   
  }

  
  
}

void forward(){
  analogWrite(ENA, MOTORA);
  analogWrite(ENB, MOTORB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("Forward");
}

void back() {
  analogWrite(ENA, MOTORA);
  analogWrite(ENB, MOTORB);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Serial.println("Back");
}

void right() {
  analogWrite(ENA, MOTORA);
  analogWrite(ENB, MOTORB);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Serial.println("Right");
}

void left() {
  analogWrite(ENA, MOTORA);
  analogWrite(ENB, MOTORB);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("Left");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
 // Serial.println("Stop!");
}

void comparison(){
  // Cheching MOTORB is quicker than MOTORA
  MA1 = pulseIn(tachA, HIGH);
  MB1 = pulseIn(tachB, HIGH);
  MA2 = pulseIn(tachA, HIGH);
  MB2 = pulseIn(tachB, HIGH);
  MA3 = pulseIn(tachA, HIGH);
  MB3 = pulseIn(tachB, HIGH);
  MA4 = pulseIn(tachA, HIGH);
  MB4 = pulseIn(tachB, HIGH);
  MA5 = pulseIn(tachA, HIGH);
  MB5 = pulseIn(tachB, HIGH);
  MA6 = pulseIn(tachA, HIGH);
  MB6 = pulseIn(tachB, HIGH);
  MA7 = pulseIn(tachA, HIGH);
  MB7 = pulseIn(tachB, HIGH);
  MA8 = pulseIn(tachA, HIGH);
  MB8 = pulseIn(tachB, HIGH);
  MA9 = pulseIn(tachA, HIGH);
  MB9 = pulseIn(tachB, HIGH);
  MA10 = pulseIn(tachA, HIGH);
  MB10 = pulseIn(tachB, HIGH);
  MA11 = pulseIn(tachA, HIGH);
  MB11 = pulseIn(tachB, HIGH);
  MA12 = pulseIn(tachA, HIGH);
  MB12 = pulseIn(tachB, HIGH);
  widthA = ((MA1 + MA2 + MA3 + MA4 + MA5 + MA6 + MA7 + MA8 + MA9 + MA10 + MA11 + MA12)/120); // Averages the values if the value of 60 is increased by a power of 10 it
  widthB = ((MB1 + MB2 + MB3 + MB4 + MB5 + MB6 + MB7 + MB8 + MB9 + MB10 + MB11 + MB12)/120); //reduces the accuracy
  Serial.print("This is widthA: ");
  Serial.println(widthA);
  Serial.print("This is MOTORA: ");
  Serial.println(MOTORA);
  Serial.print("This is widthB: ");
  Serial.println(widthB);
  Serial.print("This is MOTORB: ");
  Serial.println(MOTORB);
  
  if((widthA > widthB) && (MOTORB >= 150)){
    MOTORB--;
    }
  else if((widthA < widthB) && (MOTORB < 250)){
    MOTORB++;
    }
  else if((widthA < widthB) && (MOTORB >= 250 )){
    MOTORB -= 10;
    }
  else if(MOTORB < 150 ){
    MOTORA == 0;
    MOTORB == 0;
    }  
  else{
    Serial.println("SYNCHED");
    }
}



void WhiteLineFollowing(){
  for(;;){
    LeftTest = analogRead(LWL);
    MiddleTest = analogRead(MWL);
    RightTest = analogRead(RWL);
    MOTORA = 150;
    MOTORB = 150;
    
    //Analogue reading of white is less than the analogue reading of black
    if((LeftTest > ThreshL)&& (RightTest > ThreshR) && (MiddleTest < ThreshM)){  // M = White with R && L = Black
      forward();
      Serial.println("Middle ");
    }
    else if((LeftTest < ThreshL)&& (RightTest > ThreshR) && (MiddleTest < ThreshM)){//L = M = White R = Black
      left();
      delay(10);
      forward();
      delay(5);
      Serial.println("Swerving Left ");
    }
    else if((LeftTest > ThreshL)&& (RightTest < ThreshR) && (MiddleTest < ThreshM)){ //R = M = White and L = Black
      right();
      delay(10);
      forward();
      delay(5);
      Serial.println("Swerving Right ");
    }
    else if((LeftTest < ThreshL)&& (RightTest > ThreshR) && (MiddleTest > ThreshM)){ //L = White & R = M = Black
      left();
      delay(10);
      forward();
      delay(5);
      Serial.println("Swerving Left Only ");
    }
     else if((LeftTest > ThreshL)&& (RightTest < ThreshR) && (MiddleTest > ThreshM)){ //R = White & L = M = Black
      right();
      delay(10);
      forward();
      delay(5);
      Serial.println("Swerving Right Only ");
    }
    /*else if((LeftTest < ThreshL)&& (RightTest < ThreshR) && (MiddleTest < ThreshM)){ //R = M = L = White
      stop();
      delay(10);
      forward();
      delay(10);
      Serial.println("All White ");
    }
    else if((LeftTest > ThreshL)&& (RightTest > ThreshR) && (MiddleTest > ThreshM)){ //R = M = L = Black
      stop();
      delay(10);
      forward();
      delay(10);
      Serial.println("All Black ");
    }*/ //Purely for testing the sensors are detecting black and white correctly 
    else{
      forward();
      Serial.println("Unsure ");
      }
  }
}

void ADCWhite(){
  LeftWhite = analogRead(LWL);
  MiddleWhite = analogRead(MWL);
  RightWhite = analogRead(RWL); 
  Serial.print("Left white is: ");
  Serial.println(LeftWhite);
  Serial.print("Middle white is: ");
  Serial.println(MiddleWhite);
  Serial.print("Right white is: ");
  Serial.println(RightWhite);
}
void ADCBlack(){
  LeftBlack = analogRead(LWL);
  MiddleBlack = analogRead(MWL);
  RightBlack = analogRead(RWL);
  Serial.print("Left Black is: "); 
  Serial.println(LeftBlack);
  Serial.print("Middle Black is: ");
  Serial.println(MiddleBlack);
  Serial.print("Right Black is: ");
  Serial.println(RightBlack);
  ADCThresholds();
}
void ADCThresholds(){
  ThreshL = ((LeftBlack + LeftWhite)/2);
  ThreshM = ((MiddleBlack + MiddleWhite)/2);
  ThreshR = ((RightBlack + RightWhite)/2);
  Serial.print("Threshold for Left is: ");
  Serial.println(ThreshL);
  Serial.print("Threshold for Middle is: ");
  Serial.println(ThreshM);
  Serial.print("Threshold for Right is: ");
  Serial.println(ThreshR);
  ThresholdComplete = 1;
  delay(100);
}

void WhiteLineSensors(){
  delay(10);
  while((LeftWhite == 0)||(MiddleWhite == 0)||(RightWhite == 0)){
  if(digitalRead(FR) == HIGH){
   ADCWhite();
   }
  else{
    
  }
 }
  while((LeftBlack == 0)||(MiddleBlack == 0)||(RightBlack == 0)){
  if(digitalRead(BR) == HIGH){
    ADCBlack();
  }
  else{
    
  }
  } 
  //exit(1);
  }

