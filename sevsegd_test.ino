//defining variables.

#include <SevSeg.h>
SevSeg sevseg;

#include <LiquidCrystal.h>
LiquidCrystal LCD(8,3,16,17,18,19);

//float test=134.58;
int trigpin=15;
int ecopin=14;
float pingtime;
float distance=10.0; //cm
float sos;
int x=1;
int printtime=30;
float tem;


void setup() {

  LCD.begin(16,2);
  LCD.setCursor(6,1);
  LCD.print("HELLO");
  delay(2500);
  
  Serial.begin(2000000);
  pinMode(trigpin,OUTPUT);
  pinMode(ecopin,INPUT);
  
  byte numDigits=3;
  byte digitPins[]={11, 12, 13};
  byte segmentPins[]={7 , 6, 4, 2 , 1, 9, 10, 5};
  bool resistorsonSegments=false;
  byte hardwareConfig=COMMON_ANODE;
  bool updateWithDelays=true;
  bool leadingZeros=false;
  bool disableDecPoint=false;

  sevseg.begin(hardwareConfig ,numDigits ,digitPins ,segmentPins ,resistorsonSegments, updateWithDelays ,leadingZeros ,disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {


//RELEASING A SOUND PULSE FROM TRIGER MOD.
  digitalWrite(trigpin,LOW);
  delay(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

//RECIVING THE IMPULSE.
  pingtime=pulseIn(ecopin,HIGH);
  sos=distance/pingtime;
  sos=sos*(1.0/100.0)*(1000000.0/1.0);
  sos=sos-10;
  tem=((sos-331.0)/(0.61));
  Serial.print(sos);
  Serial.print(": ");
  Serial.println(tem);
  delayMicroseconds(1);

//DISPLAYING IT ON TO THE SEV_SEG DIS.   
  while (x<=printtime){
   sevseg.setNumber(sos,0);
   sevseg.refreshDisplay();
   x=x+1;
   LCD.clear();
   LCD.setCursor(0,0);
   LCD.print("TEMPRATURE:-");
   LCD.setCursor(0,1);
   LCD.print(tem);
   LCD.setCursor(5,1);
   LCD.print("*C");
  }
  x=1;
}
