#include<LiquidCrystal_I2C.h>
#include<UltraDistSensor.h>
//#include<SPI.h>
//#include <Adafruit_GFX.h>
//#include<Max72xxPanel.h>
#include<MD_Parola.h>
#include<MD_MAX72xx.h>
#include<SPI.h>
#include<LedControl.h>
#include "DHT.h"
#include<Wire.h>


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW


#define DHTPIN 4
#define DHTTYPE DHT11

#define CS_MATRIX 10
#define  CLK_MATRIX 7
#define DATA_MATRIX 11




LiquidCrystal_I2C lcd(0x27,16,2);//set the LCD address for 16 hcars and 2 lines

DHT dht(DHTPIN,DHTTYPE);
UltraDistSensor mysensor;



//skull char
byte Skull[8]={
0b00000,
0b01110,
0b10101,
0b11011,
0b01110,
0b01010,
0b00000,
0b00000
};
//char char
byte Car[]={
B000000,
B000000,
B000000,
B000100,
B001010,
B011111,
B001010,
B000000
};



//pins matrix
int cs_matrix= 10;
int clk_matrix=7;
int data_matrix=11;

//initializare matrix
//Max72xxPanel matrix = Max72xxPanel(cs_matrix,1,1);
//MD_MAX72XX matrix =MD_MAX72XX(MD_MAX72XX::PAROLA_HW,CS_MATRIX,1);
LedControl matrix =LedControl(data_matrix,clk_matrix,cs_matrix,0);
//MD_Parola matrix = MD_Parola(MD_MAX72XX::PAROLA_HW,CS_MATRIX,1);

//define heart for matrix
byte hearth[]={
B00011000,
B00111100,
B01111110,
B11111111,
B11111111,
B11111111,
B01100110,
B00000000

 
};
byte leftarrow[]={
B00001000,
B00000100,
B00000010,
B11111111,
B00000010,
B00000100,
B00001000,
B00000000

};
byte rightarrow[]={
B00010000,
B00100000,
B01000000,
B11111111,
B01000000,
B00100000,
B00010000,
B00000000

};



//flame senzor
const int sensorMin=0;
const int sensorMax =1024;




//define pin buzzer
const int buzzerPin =8;



//define pins number
const int trig =12;
const int echo = 13;



//variables ultrasonic senzor

//const int trig =10;
//const int echo = 11;
//variables ultrasonic senzor
long duration;
int distanceCm,distanceInch;

float reading;
float reading2;




//pins 8key sensor pins
// Touch sensor pin definitions
const int touchPin1 = 3;
const int touchPin2 = 5;
const int touchPin3 = 6;
const int touchPin4 = 9;
const int touchPin5 = 14;
const int touchPin6 = 15;
const int touchPin7 = 16;
const int touchPin8 = 2;
  

void setup() {
  // Serial begin
 // pinMode(buzzerPin, OUTPUT);
 Serial.begin(9600);
 //sets pins ultrasonic senzor
 /*pinMode(trig, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo, INPUT);*/

mysensor.attach(12,13);
 
 pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  
//clearMatrix();
 // Touch module sensor
  pinMode(touchPin1, INPUT);
  pinMode(touchPin2, INPUT);
  pinMode(touchPin3, INPUT);
  pinMode(touchPin4, INPUT);
  pinMode(touchPin5, INPUT);
  pinMode(touchPin6, INPUT);
  pinMode(touchPin7, INPUT);
  pinMode(touchPin8, INPUT);

  

  // DHT sensor
  dht.begin();

  // LCD initialization
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(1, Car);

  // Matrix initialization
 
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 15);
  matrix.clearDisplay(0);

  // Display startup message on LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  
  lcd.print("FORVIA HELLA");

  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start PROJECT");
  delay(5000);








}

void loop() {


  //SENSOR TOUCH MODULE
  int touchState1 = digitalRead(touchPin1);
  int touchState2 = digitalRead(touchPin2);
  int touchState3 = digitalRead(touchPin3);
  int touchState4 = digitalRead(touchPin4);
  int touchState5 = digitalRead(touchPin5);
  int touchState6 = digitalRead(touchPin6);
  int touchState7 = digitalRead(touchPin7);
  int touchState8 = digitalRead(touchPin8);

 lcd.setCursor(0,0);

reading = mysensor.distanceInCm();
reading2 = mysensor.distanceInInch();
Serial.println(reading);
Serial.println(reading2);
  if(reading<10 && reading>5){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist Cm:");
  lcd.print(reading);
  lcd.setCursor(0, 1);
  lcd.print("Dist Inch:");
  lcd.print(reading2);
  delay(1000);
  }else if(reading<5){
    while(reading<5){
      reading = mysensor.distanceInCm();
     lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist Cm:");
  lcd.print(reading);
  lcd.setCursor(0, 1);
  lcd.print("Dist Inch:");
  lcd.print(reading2);
  delay(1000);
  activateBuzzer(10);
  delay(500);
  }
  }
 
 
  

//flame sensor activation
int sensorRead = analogRead(A3);
int range = map(sensorRead,sensorMin,sensorMax,0,3);

if(range==0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Close Fire!");
    buzzerfiresensor();
    delay(3000);
    dezactivateBuzzer();
    lcd.clear();
}
else if(range ==1){

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Distant Fire");
    activateBuzzer(5);
    delay(3000);
    dezactivateBuzzer();
    lcd.clear();
}

  




 


 if (touchState1 == HIGH) {
   // Add a small delay for debouncing
 
    // Touch is still detected after the delay
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Key 1 pressed");
    Serial.println("Key 1 pressed");
   // leftarrow_anim();
   displayMatrix(leftarrow);
    delay(1000);
    clearMatrix();
 //   matrix.displayText("->",PA_RIGHT, 2, 1,PA_SCROLL_RIGHT );
    //clearMatrix();
    //displayMatrix(leftarrow);
  

} else if (touchState2 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Key 2 pressed");
  Serial.println("Key 2 pressed");
  displayMatrix(rightarrow);
  delay(1000);
  clearMatrix();
} else if (touchState3 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Key 3 pressed");
   Serial.println("Key 3 pressed");
  humitemp_sensor();
} else if (touchState4 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Key 4 pressed");
   Serial.println("Key 4 pressed");
   for(int i=1;i<21;i++){
  displayMatrix(hearth);
  delay(10);
  clearMatrix();
   }
} else if (touchState5 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  for(int i=0;i<16;i++){
    lcd.setCursor(i, 0);
    lcd.write(byte(1));
    delay(1000);
    lcd.clear();
    delay(100);
  }
   lcd.clear();
  lcd.setCursor(0, 1);
  
  for(int i=0;i<16;i++){
    lcd.setCursor(i, 1);
    lcd.write(byte(1));
    delay(1000);
    lcd.clear();
    delay(100);
    
  }
} else if (touchState6 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to your car!");
  delay(1500);
   for(int i =0;i<31;i++){
  lcd.scrollDisplayLeft();
  delay(1000);
   }
  lcd.setCursor(1, 0);
  lcd.clear();
  lcd.print("Please but the belly!");
  delay(1500);
  for(int i =0;i<31;i++){
  lcd.scrollDisplayLeft();
  delay(1000);
  }
   Serial.println("Key 6 pressed");
} else if (touchState7 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Key 7 pressed");
   Serial.println("Key 7 pressed");
} else if (touchState8 == HIGH) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Key 8 pressed");
   Serial.println("Key 8 pressed");
}






    
 

 
 
 
  /* put your main code here, to run repeatedly:
  displayMatrix(hearth);
  delay(100);
  //digitalWrite(buzzerPin,HIGH);
 
  for(int i=0;i<=10;i++){
    digitalWrite(buzzerPin,LOW);
    delay(50);
    digitalWrite(buzzerPin,HIGH);
    delay(50);


  }
  
  
  //activate led
  lcd.clear();
 digitalWrite(2,HIGH);
 //set cursor lcd to 0,0
lcd.setCursor(0,0);

//flame sensor activation
int sensorRead = analogRead(A3);
int range = map(sensorRead,sensorMin,sensorMax,0,3);



/*for(int i =0;i<16;i++){
  lcd.setCursor(i,1);
  lcd.write(1);
  delay(500);
  lcd.clear();

}

delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("TEST1");
delay(3000);
*/













delay(3000);
lcd.clear();
}





void humitemp_sensor(){
  //read humidity
delay(200);
float humidity = dht.readHumidity();
//read temerature in Celsius
float temperature =dht.readTemperature();

delay(100);
//check if is any error reading temperature
if(isnan(humidity)||isnan(temperature)){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Failed");
}else{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humi:");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C"); 
  delay(3000);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,1);
}
}


void activateBuzzer(unsigned long duration) {
  digitalWrite(buzzerPin, LOW);
  delay(duration);
  dezactivateBuzzer();
  
 
}



void dezactivateBuzzer(){
 digitalWrite(buzzerPin, HIGH);
}


void displayMatrix(byte pattern[]) {
  for (int i = 0; i < 8; i++) {
    matrix.setColumn(0, i, pattern[i]);
    
    delay(10);
  }
}



void clearMatrix() {
  for (int i = 0; i < 8; i++) {
    matrix.setColumn(0, i, 0);
    
    delay(10);
  }
}

void buzzerfiresensor(){
 digitalWrite(buzzerPin, LOW); 
}





