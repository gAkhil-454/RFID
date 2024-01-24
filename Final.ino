#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#define led D0
#define red D3
#define ser D8
#define buz D4
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
MFRC522 mfrc522(SS_PIN, RST_PIN); /servo pins
Servo s1;


char auth[] = "EYmXq_mLy2RiEDSkUhBy2HgGuWFUmopw";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pixel_6a";
char pass[] = "chaitu@2002";
BlynkTimer timer;



void setup() {
  pinMode(led , OUTPUT);
  
  pinMode(red , OUTPUT);
  s1.attach(ser);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass ,"blynk.cloud", 80);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  

}



void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.println(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "83 6B 82 06") //change UID of the card that you want to give access
  {
    Serial.println(" Authorized Access ");
    Blynk.logEvent(5940);
    digitalWrite(led , HIGH);
    
    delay(400);
    digitalWrite(led , LOW );
    s1.write(180);
    
    delay(1000);

  }
  
  else   {
    Serial.println(" Access Denied ");
    Blynk.logEvent(5941);
     digitalWrite(red , HIGH);
    delay(400);
    digitalWrite(red , LOW );
    s1.write(0);
    delay(400);
  }

  s1.write(0);

}
//void sendSensor(){
//  if ( ! mfrc522.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) 
//  {
//    return;
//  }
//  //Show UID on serial monitor
//  Serial.println();
//  Serial.println(" UID tag :");
//  String content= "";
//  byte letter;
//  for (byte i = 0; i < mfrc522.uid.size; i++) 
//  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//  }
//  content.toUpperCase();
//  Serial.println();
//  if (content.substring(1) == "83 6B 82 06") //change UID of the card that you want to give access
//  {
//    Serial.println(" Authorized Access ");
//    Serial.println(" Welcome to my channel Mostly Programing ");
//    Blynk.logEvent(5940);
//    digitalWrite(D0 , HIGH);
//    delay(1000);
//
//  }
//  
//  else   {
//    Serial.println(" Access Denied ");
//    digitalWrite(D0 , LOW);
//    delay(400);
//  }
//  
//}
