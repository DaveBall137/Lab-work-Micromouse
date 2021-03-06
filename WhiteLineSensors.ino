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

  int FR = 50; //setting pin 50 to the Front Right sensor
  int FL = 51; //setting pin 51 to the Front Left sensor
  int BL = 52; //setting pin 52 to the Back Left sensor
  int BR = 53; //setting pin 53 to the Back Right sensor
  
  
void setup() {
  // put your setup code here, to run once:
  pinMode(PWL, OUTPUT);
  pinMode(ZWL, OUTPUT);
  Serial.begin(9600);
  digitalWrite(PWL, HIGH);
  digitalWrite(ZWL, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  if(digitalRead(FR) == HIGH){
   ADCWhite();
   }
  else if(digitalRead(BR) == HIGH){
    ADCBlack();
  }
  else if(digitalRead(FL) == HIGH){
    ADCThresholds();
  }
  else{
    
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
}
void ADCThresholds(){
  float ThreshL = ((LeftBlack + LeftWhite)/2);
  float ThreshM = ((MiddleBlack + MiddleWhite)/2);
  float ThreshR = ((RightBlack + RightWhite)/2);
  Serial.print("Threshold for Left is: ");
  Serial.println(ThreshL);
  Serial.print("Threshold for Middle is: ");
  Serial.println(ThreshM);
  Serial.print("Threshold for Right is: ");
  Serial.println(ThreshR);
}
