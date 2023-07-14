#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);//set the LCD address for 16 hcars and 2 lines
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
byte Car[8]={
0b00000,
0b00000,
0b00000,
0b00100,
0b01010,
0b11111,
0b01010,
0b00000
};
//create skull character



//define pins number
const int trig =10;
const int echo = 11;

long duration;
int distanceCm,distanceInch;
void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.clear();
lcd.backlight();
lcd.createChar(0,Skull);
lcd.createChar(1,Car);
lcd.setCursor(2,0);
lcd.write(0);
lcd.print("Smart CarACCES!");
lcd.write(0);
delay(5000);

//sets pins ultrasonic senzor
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
lcd.setCursor(0,1);
for(int i =0;i<16;i++){
  lcd.setCursor(i,1);
  lcd.write(1);
  delay(500);
  lcd.clear();

}
delay(1000);
lcd.clear();
//ultrasonic senzor
/*digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

//Masurare timpului de receptie a echo
duration=pulseIn(echo,HIGH);
distanceCm = duration * 0.034555/2;
distanceInch = duration * 0.013555/2;
lcd.setCursor(0,0);
lcd.write("Distance:");
lcd.write(distanceCm);
lcd.write(" cm");
delay(10);
lcd.setCursor(0,1);
lcd.write("Distance:");
lcd.write(distanceInch);
lcd.write(" Inch");
delay(10000);
*/


}
