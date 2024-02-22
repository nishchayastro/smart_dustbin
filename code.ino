#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM900A(8,9);

//LiquidCrystal lcd(8,9,10,11,12,13);//RS,EN,D4,D5,D6,D7
#define ir1 4
#define sen1 A0 // moisture
#define buzzer 10

#define trigPin1 7////right
#define echoPin1 6

#define trigPin2 2  //// front
#define echoPin2 5
int onetime=0,onetime1=0 ;
int pos =100;
int wet=0,moisture=0,object=0,cabin2=0,c1=0,c2=0;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most board

void setup() 
{SIM900A.begin(9600);   
 Serial.begin(9600);
// lcd.begin(16, 2);//initializing LCD
 //lcd.setCursor(0,0); 
 //lcd.print("Automatic WASTE");
// lcd.setCursor(0,1); 
// lcd.print("Segregation sys");
 delay(3000);
 pinMode(ir1,INPUT);
 pinMode(sen1,INPUT);
 pinMode(buzzer,OUTPUT);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 myservo.attach(3);  // attaches the servo on pin 9 to the servo object
 myservo.write(95);
 delay(3000);
}
 void ultrasensor(int trigPin,int echoPin)
 { 
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
int  duration = pulseIn(echoPin, HIGH);
int  distance = (duration/2) / 29.1;
 }
void loop() 
{
 moisture=analogRead(sen1);
 Serial.print("moisture sensor= ");
 Serial.println(moisture);
 delay(500);

 //int distance;
 long duration1, distance1;
 digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*0.034/2;
int sensor1 = distance1;
 //delay(10);
  /////////////////////////////////////////////////////
  long duration2, distance2;
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2= duration2*0.034/2;
 int sensor2 = distance2;    
 // delay(10);
  
 // Serial.println(sensor1);
  //Serial.println(sensor2);
  Serial.print("distance1=");
  Serial.println(distance1);
  Serial.println("distance2=");
  Serial.print(distance2);
  
  //int lvl1=(16-sensor1)*6.5;
  //int lvl2=(16-sensor2)*6.5;
 // Serial.print("distance1=");
  // Serial.println(distance1);
  // Serial.print("distance2=");
  //Serial.println(distance2);
   //if(distance1>distance2)
//  {lcd.clear();
  //lcd.setCursor(0,0); 
  //lcd.print("dry: ");
  //lcd.setCursor(12,0); 
 // lcd.print(distance1);}
  //delay(1000);
  //if(distance2>distance1)
//  {lcd.clear();
 // lcd.setCursor(0,1); 
  //lcd.print("wet ");
  //lcd.setCursor(4,1); 
  //lcd.print(distance2);
  //lcd.setCursor(8,1); 
 // lcd.print("WL= ");
  //lcd.setCursor(13,1); 
  //lcd.print(lvl2);
  //delay(1000);}
 if(distance2<=100 && distance1>=150)
  {      
   if(onetime==0)
   {
//     lcd.setCursor(0,0); 
//  lcd.print("-send msg-");
    digitalWrite(buzzer,HIGH); 
    tracking1(); 
    delay(3000);
    digitalWrite(buzzer,LOW);
    onetime=1;
   }
  }
   
  else if (distance1<=12|| distance2<=12)
  {
    if(onetime1==0)
    {
//      lcd.setCursor(0,0); 
//  lcd.print("-send msg-");
     digitalWrite(buzzer,HIGH); 
     tracking();
    delay(3000);
     digitalWrite(buzzer,LOW);
     onetime1=1; 
    }
  }
else
{
 onetime=0;
 onetime1=0;
}
/////////////////////////////////////////////////////
  object=digitalRead(ir1);
  moisture=analogRead(sen1);
 if(object==LOW)
  {
   moisture=analogRead(sen1);
//   lcd.setCursor(0,0); 
//   lcd.print("-GARBAGE SENSE-");
   digitalWrite(buzzer,HIGH);
   delay(150);
   digitalWrite(buzzer,LOW);
   delay(1000);
   moisture=analogRead(sen1);
   Serial.print("moisture = ");
   Serial.println(moisture);
   delay(500);
   //moisture=analogRead(sen1);
   //Serial.print("moisture = ");
   //Serial.println(moisture);
   //delay(500);
   //delay(2000);
   if(moisture>=1000)                         
   {
//    lcd.setCursor(0,0); 
//    lcd.print(" WET  GARBAGE");
    
  myservo.write(100);
    delay(500);
    myservo.write(180);
    delay(2000);
    myservo.write(100);
   }
   else
   {  
 //   lcd.setCursor(0,0); 
//    lcd.print(" dry  GARBAGE");
   myservo.write(100);
    delay(500);
    myservo.write(0);
    delay(2000);
    myservo.write(100);
    
    Serial.println("DRY");
//    lcd.clear();
   } 
    
  } 
        
}

 
 //void init_sms()
 //{
 // Serial.println("AT+CMGF=1");
  //delay(400);
  //Serial.println("AT+CMGS=\"+918292056200\"");   // use your 10 digit cell no. here
  //delay(400);
 //}

  
// void send_data(String message)
 //{
 // Serial.println(message);
 // delay(200);
 //}
 
 //void send_sms()
 //{
 // Serial.write(26);
 //}
 void tracking1()
 {
  
Serial.println ("Sending Message please wait....");
  SIM900A.println("AT+CMGF=1");    //Text Mode initialisation 
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+918853814531\"\r"); // Receiver's Mobile Number
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("your dustbin is full ");// Messsage content
  delay(100); 
 // Serial.println("ATD+918750522729;");
  Serial.println ("Done");
  SIM900A.println((char)26);//   delay(1000);
  Serial.println ("Message sent succesfully");
 }
  void tracking()
 {
  Serial.println ("Sending Message please wait....");
  SIM900A.println("AT+CMGF=1");    //Text Mode initialisation 
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+917277514262\"\r"); // Receiver's Mobile Number
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("your dustbin is full");// Messsage content
  delay(100); 
 // Serial.println("ATD+918750522729;");
  Serial.println ("Done");
  SIM900A.println((char)26);//   delay(1000);
  Serial.println ("Message sent succesfully");
 }
