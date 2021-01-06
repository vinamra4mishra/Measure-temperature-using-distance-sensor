#include <LiquidCrystal.h>
LiquidCrystal LCD(10, 9, 8, 7 , 6, 5);

//DEFINING PINS.
int rled=4;
int gled=2;
int bled=3;

int redpot=19;
int greenpot=18;
int bluepot=17;

int navpot=14;
int lock=15; 

//DEFINING VARIABLES.

float navigationval;
int lockval;

int Rvalue;
int Gvalue;
int Bvalue;

int rw;
int gw;
int bw;

int R;
int G;
int B;
int n=600;

float highval=1000;

int slowmodewaittime=450;

void setup() { 
  Serial.begin(2000000);
  
  pinMode(navpot,INPUT);
  pinMode(lock,INPUT);
   
  pinMode(redpot,INPUT);
  pinMode(greenpot,INPUT);
  pinMode(bluepot,INPUT);
  
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(bled,OUTPUT);

  LCD.begin(16,2);
  LCD.setCursor(5,1);
  LCD.print("HELLO");
  delay(300);  
}


void loop() {
  
navigationval=analogRead(navpot);
navigationval=map(navigationval, 0, 1023, 0, 300);
Serial.println(navigationval);

while(navigationval<=150){
  
    LCD.clear(); 
    LCD.setCursor(2,1);
    LCD.print("COLOUR MIXER");  
    delay(10);
    
  lockval=digitalRead(lock);
  navigationval=analogRead(navpot);
  navigationval=map(navigationval, 0, 1023, 0, 300 );
  Serial.println(navigationval);

  while(lockval<=0){
    
  lockval=digitalRead(lock);
  Rvalue=analogRead(redpot);
  Gvalue=analogRead(greenpot);
  Bvalue=analogRead(bluepot);

  rw=map(Rvalue, 0, 1023, 0, highval);
  gw=map(Gvalue, 0, 1023, 0, highval);
  bw=map(Bvalue, 0, 1023, 0, highval);
  
  R=map(rw, 0, highval, 0, 101);                   //R=map(rw, 0, highval, 0, 100);
  G=map(gw, 0, highval, 0, 101);                   //G=map(gw, 0, highval, 0, 101);
  B=map(bw, 0, highval, 0, 101);                   //B=map(bw, 0, highval, 0, 100);
  

  delay(7);
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("RED");
  LCD.setCursor(5,0);
  LCD.print("GREEN");
  LCD.setCursor(12,0);
  LCD.print("BLUE");
  LCD.setCursor(0,1);
  LCD.print(R);
  LCD.setCursor(5,1);
  LCD.print(G);
  LCD.setCursor(12,1);
  LCD.print(B);

  digitalWrite(rled,LOW);
  delayMicroseconds(rw);   //rw
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  delayMicroseconds(gw);  //gw
  digitalWrite(gled,HIGH);
  digitalWrite(bled,LOW);
  delayMicroseconds(bw);  //bw
  digitalWrite(bled,HIGH);
  }
}
while(navigationval>=150){
  
  LCD.clear(); 
  LCD.setCursor(3,1);
  LCD.print("SLOW MODE");
  delay(50);

  lockval=digitalRead(lock);
  navigationval=analogRead(navpot);
  navigationval=map(navigationval, 0, 1023, 0, 300 );
  Serial.println(navigationval);

    while(lockval<=0){
     
  lockval=digitalRead(lock);
  slowmodewaittime=analogRead(navpot);
  slowmodewaittime=map(slowmodewaittime, 0, 1023, 1, n);
  
  digitalWrite(rled,LOW);
  LCD.clear(); 
  LCD.setCursor(6,1);
  LCD.print("RED");
  slowmodewaittime=analogRead(navpot);
  slowmodewaittime=map(slowmodewaittime, 0, 1023, 0, n); 
  delay(slowmodewaittime);   
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  LCD.clear(); 
  LCD.setCursor(5,1);
  LCD.print("GREEN"); 
  slowmodewaittime=analogRead(navpot);
  slowmodewaittime=map(slowmodewaittime, 0, 1023, 1, n); 
  delay(slowmodewaittime);  
  digitalWrite(gled,HIGH);
  digitalWrite(bled,LOW);
  LCD.clear(); 
  LCD.setCursor(6,1);
  LCD.print("BLUE");  
  delay(slowmodewaittime); 
  slowmodewaittime=analogRead(navpot);
  slowmodewaittime=map(slowmodewaittime, 0, 1023, 1, n); 
  digitalWrite(bled,HIGH);   
    }
}
}
