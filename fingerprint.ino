#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(5, 6);
#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
boolean b=false;
boolean e=true;
boolean f=true;
int k=0;
int o=0;
byte isi;
int alamat = 0;
int nyala=9;
int ampli=10;
int daftar=7;
int hapus=8;
int relaystart=2;
int relaykontak=3;
void setup() {
  pinMode(daftar,INPUT_PULLUP);
  pinMode(hapus,INPUT_PULLUP);
  pinMode(nyala,OUTPUT);
  pinMode(ampli,OUTPUT);
  digitalWrite(nyala,HIGH);
  pinMode(relaystart,OUTPUT);
  pinMode(relaykontak,OUTPUT);
  Serial.begin(9600);
  mp3_set_serial (Serial);
  mp3_set_volume (30);
  finger.begin(57600);
  if (finger.verifyPassword()) {
    //Serial.println("Found fingerprint sensor!");
  } else {
    //Serial.println("Did not find fingerprint sensor :(");
    while (1) {delay(1);}
  }
  digitalWrite(ampli,LOW);
}

void loop() {
  isi=EEPROM.read(alamat);
  if(isi>50){
     EEPROM.write(0, 0);
  }
  e=digitalRead(daftar);
  f=digitalRead(hapus);
  while(!e){e
    
    mp3_play (5);
    getFingerprintEnroll(isi);
    delay(1000);
    e=digitalRead(daftar);
    if(isi<50){
    isi+=1;
    }
    
    delay(100);
  }
  if(!f){
    
    mp3_play (9);
    finger.emptyDatabase();
  while(!f){
    f=digitalRead(hapus);
    delay(100);
  }
  }
  b =digitalRead(relaykontak);
  getFingerprintIDez();
  delay(10);
  //digitalWrite(ampli,LOW);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
     
     
  delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
   
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
  
      return p;
    case FINGERPRINT_IMAGEFAIL:
   
      return p;
    default:
   
      return p;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
   
  delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
   
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    
      return p;
    case FINGERPRINT_FEATUREFAIL:
   
      return p;
    case FINGERPRINT_INVALIDIMAGE:
     
      return p;
    default:
   
      return p;
  }
  
 
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
   
  
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
  
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
 
    return p;
  } else {
  
    return p;
  }   
  
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  
  {
    
    //Serial.println("Salah");
    //mp3_play (4);
    k+=1;
    finger.salah();
     while (p != FINGERPRINT_NOFINGER) {
      
    p = finger.getImage();
    //Serial.println("Lepaskan");
    delay(1000);
  }
  finger.mati1();
  
  delay(2000);
  if(k>2){
    mp3_play (4);
    k=0;
     //Serial.println("kunci");
     int u=0;
    while (u<60){
    delay(1000);
    u++;
    //Serial.println("kunci");
    }
    digitalWrite(nyala,LOW);
  }
  return -1;
  }
 k=0;
 
 if(!b){
  
  int tegangan=analogRead(0);
  float volt = tegangan * (5.0 / 1023.0);
  volt=volt/0.2481;
  digitalWrite(relaykontak,HIGH);
  finger.lampu();
  //Serial.println("kontak");
  if(volt>=12)
  mp3_play (1);  //Suara yang sudah disiapkan dengan nama file 0001
  else mp3_play (2);
  o=0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
//    o++;
//    //Serial.println("Lepaskan");
//    if(o>3){
//      finger.start();
//      //mp3_play (2);
////delay(2000);
//digitalWrite(relaystart,HIGH);
////Serial.println("menyalakan mesin");
////a=digitalRead(aktif);
//p = 0;
//  while (p != FINGERPRINT_NOFINGER) {
//    p = finger.getImage();
//  }
////Serial.println("mematikan starter");
//digitalWrite(relaystart,LOW);
//   finger.mati2();
//   goto serius;
//    }
    delay(500);
    
  }
  
 //Serial.println("Dilepaskan");
for(int a=0;a<50;a++){
   //Serial.println(a);
uint8_t p = finger.getImage();
  if (p == FINGERPRINT_OK)  {

  p = finger.image2Tz();
  if (p == FINGERPRINT_OK)  {

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK)  
  {
  //Serial.println("berhasil");
  goto starter;
  }
  }
  }
  delay(1000);
  if(a>=25){goto mati;}
   
 }
  starter:
  //mp3_play (2);
 //delay(2000);
 //digitalWrite(ampli,LOW);
digitalWrite(relaystart,HIGH);
//Serial.println("menyalakan mesin");
//a=digitalRead(aktif);
p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
//Serial.println("mematikan starter");
//delay(1200);
digitalWrite(relaystart,LOW);
 }
 else{
   mati:
   
   finger.mati3();
    mp3_play (3);
   delay(7000);
  digitalWrite(relaykontak,LOW); 
  delay(1000);
  //Serial.println("mematikan motor");
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  delay(5000);
  digitalWrite(nyala,LOW);
 }
    serius:
  

  return finger.fingerID; 
}

//daftar
uint8_t getFingerprintEnroll(int id) {
  int p = -1;
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
  
      break;
    case FINGERPRINT_NOFINGER:
   
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
     
      break;
    case FINGERPRINT_IMAGEFAIL:
    
      break;
    default:
   
      break;
    }
  }

 

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
   
      break;
    case FINGERPRINT_IMAGEMESS:
    
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
   
      return p;
    case FINGERPRINT_FEATUREFAIL:
   
      return p;
    case FINGERPRINT_INVALIDIMAGE:
     
      return p;
    default:
   
      return p;
  }
  mp3_play (6);
  //Serial.println("Lepaskan jari");
  delay(2000);
 
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  p = -1;
 mp3_play (5);
   //Serial.println("Tempelkan jari");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
   
      break;
    case FINGERPRINT_NOFINGER:
   
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
    
      break;
    case FINGERPRINT_IMAGEFAIL:
   
      break;
    default:
     
      break;
    }
  }

 

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
   
      break;
    case FINGERPRINT_IMAGEMESS:
   
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
  
      return p;
    case FINGERPRINT_FEATUREFAIL:
    
      return p;
    case FINGERPRINT_INVALIDIMAGE:
  
      return p;
    default:
    
      return p;
  }
 
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
 
   
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
  
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
   
    return p;
  } else {
   
    return p;
  }   
 
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    mp3_play (7);
    // Serial.println("Disimpan");
   //EEPROM.write(alamat,2);
EEPROM.write(0, isi);
  
  while(!e){ 
    e=digitalRead(daftar);
    delay(200);
  }
  delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
   
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
  
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
 
    return p;
  } else {

    return p;
  }   
}
