// ESP
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DEBUG true
String mySSID = "robotika";       // WiFi SSID
String myPWD = "nasratpanove"; // WiFi Password
String myAPI = "ZG57XJ27ZQT2E2B9";   // API Key
String myHOST = "184.106.153.149";
String myPORT = "80";
String obyvakFIELD = "field1";
String pokojFIELD = "field2"; 
String predsinFIELD = "field3";
String techFIELD = "field4";
String odesilanaHodnota = "1";
float tepobyvak;
float vlhobyvak;
float teploznice;
float vlhloznice;
float teppracovna;
float vlhpracovna;
float tepkoupelna;
float vlhkoupelna;
int potPin0 = A0;
int potPin1 = A1;
int potPin2 = A2;
int potPin3 = A3;
int potobyvak = 0;
int potloznice = 0;
int potpracovna = 0;
int potkoupelna = 0;
int fanobyvak = 22;
int fanloznice = 23;
//DHT
#include "DHT.h"
#define pinDHT 6
#define pinDHT2 9
#define pinDHT3 10
#define pinDHT4 11
#define typDHT22 DHT22  

DHT obyvakDHT(pinDHT, typDHT22);
DHT lozniceDHT(pinDHT2, typDHT22);
DHT pracovnaDHT(pinDHT3, typDHT22);
DHT koupelnaDHT(pinDHT4, typDHT22);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int bobyvak = 3;
int robyvak1 = 2;
int bloznice = 4;
int rloznice = 5;
int robyvak2 = 7;
int rpracovna = 8;
int rkouplena = 12;
int presettemp = 25;

void setup() {
  Serial.begin(9600);
  obyvakDHT.begin();
  lozniceDHT.begin();
  pracovnaDHT.begin();
  koupelnaDHT.begin();
  pinMode(robyvak1,OUTPUT);
  pinMode(bobyvak,OUTPUT);
  pinMode(bloznice,OUTPUT);
  pinMode(rloznice,OUTPUT);
  pinMode(rpracovna,OUTPUT);
  pinMode(robyvak2, OUTPUT);
  pinMode(rkouplena,OUTPUT);
  pinMode(fanobyvak, OUTPUT);
  pinMode(fanloznice, OUTPUT);
  Serial1.begin(115200);
  espData("AT+RST", 1000, DEBUG);                      //Reset the ESP8266 module
  espData("AT+CWMODE=1", 1000, DEBUG);                 //Set the ESP mode as station mode
  espData("AT+CWJAP=\""+ mySSID +"\",\""+ myPWD +"\"", 1000, DEBUG);   //Connect to WiFi network
  espData("AT+CIFSR", 1000, DEBUG);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  potobyvak = analogRead(potPin0);
  potobyvak = map(potobyvak, 0, 1023, 15, 35);
  potloznice = analogRead(potPin1);
  potloznice = map(potloznice, 0, 1023, 15, 35);
  potpracovna = analogRead(potPin2);
  potpracovna = map(potpracovna, 0, 1023, 15, 35);
  potkoupelna = analogRead(potPin3);
  potkoupelna = map(potkoupelna, 0, 1023, 15, 35);
  tepobyvak = obyvakDHT.readTemperature();
  vlhobyvak = obyvakDHT.readHumidity();
  teploznice = lozniceDHT.readTemperature();
  vlhloznice = lozniceDHT.readHumidity();
  teppracovna = pracovnaDHT.readTemperature();
  vlhpracovna = pracovnaDHT.readHumidity();
  tepkoupelna = koupelnaDHT.readTemperature();
  vlhkoupelna = koupelnaDHT.readHumidity();
    
lcd.setCursor(0, 0);
lcd.print("Ob:");
lcd.setCursor(3, 0);
lcd.print(potobyvak);

lcd.setCursor(8, 0);
lcd.print("Lo:");
lcd.setCursor(11, 0);
lcd.print(potloznice);

lcd.setCursor(0, 1);
lcd.print("Kp:");
lcd.setCursor(3, 1);
lcd.print(potkoupelna);

lcd.setCursor(8, 1);
lcd.print("Pr:");
lcd.setCursor(11, 1);
lcd.print(potpracovna);
  
  if (isnan(tepobyvak) || isnan(vlhobyvak)){
      Serial.println("Chyba při čtení z DHT senzoru!");
    }else{
          if (tepobyvak <= potobyvak) {
      digitalWrite(bobyvak,LOW);
      digitalWrite(robyvak1,HIGH);
      digitalWrite(robyvak2, HIGH);
      digitalWrite(fanobyvak,LOW);
    /*        
    Serial.println(" ___________________________________");
    Serial.println("|Obývací pokoj:                     |");
    Serial.print("|Teplota: "); 
    Serial.print(tepobyvak);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhobyvak);
    Serial.println("  %|");
    Serial.println("|___________________________________|");     
    */        
      }else{
      digitalWrite(robyvak1, LOW);
      digitalWrite(robyvak2, LOW);
      digitalWrite(bobyvak,HIGH);
      digitalWrite(fanobyvak,HIGH);
   /*         
    Serial.println(" ___________________________________");
    Serial.println("|Obývací pokoj:                     |");
    Serial.print("|Teplota: "); 
    Serial.print(tepobyvak);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhobyvak);
    Serial.println("  %|");
    Serial.println("|___________________________________|");
   */         
      }
      }
     
      if (isnan(teploznice) || isnan(vlhloznice)){
      Serial.println("Chyba při čtení z DHT senzoru!");
    }else{
          if (teploznice <= potloznice) {
      digitalWrite(bloznice,LOW);
      digitalWrite(fanloznice, LOW);
      digitalWrite(rloznice,HIGH);
   /*
    Serial.println(" ___________________________________");
    Serial.println("|Pokoj:                            |");
    Serial.print("|Teplota: "); 
    Serial.print(teploznice);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhloznice);
    Serial.println("  %|");
    Serial.println("|___________________________________|");
    */     
      }else{
      digitalWrite(rloznice, LOW);
      digitalWrite(bloznice,HIGH);
      digitalWrite(fanloznice, HIGH);
   /*
    Serial.println(" ___________________________________");
    Serial.println("|Pokoj:                            |");
    Serial.print("|Teplota: "); 
    Serial.print(teploznice);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhloznice);
    Serial.println("  %|");
    Serial.println("|___________________________________|");
    */
      }
      }
    if (isnan(teppracovna) || isnan(vlhpracovna)){
      Serial.println("Chyba při čtení z DHT senzoru!");
    }else{
          if (teppracovna <= potpracovna) {
      digitalWrite(rpracovna,HIGH);
   /*
    Serial.println(" ___________________________________");
    Serial.println("|Předsíň:                           |");
    Serial.print("|Teplota: "); 
    Serial.print(teppracovna);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhpracovna);
    Serial.println("  %|");
    Serial.println("|___________________________________|");     
  */
      }else{
      digitalWrite(rpracovna, LOW);
  /* 
    Serial.println(" ___________________________________");
    Serial.println("|Předsíň:                           |");
    Serial.print("|Teplota: "); 
    Serial.print(teppracovna);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhpracovna);
    Serial.println("  %|");
   Serial.println("|___________________________________|");
   */
      }
      }
      if (isnan(tepkoupelna) || isnan(vlhkoupelna)){
      Serial.println("Chyba při čtení z DHT senzoru!");
    }else{
          if (tepkoupelna <= potkoupelna  ) {
      
      digitalWrite(rkouplena,HIGH);
  /*
    Serial.println(" ___________________________________");
    Serial.println("|Technická místnost:               |");
    Serial.print("|Teplota: "); 
    Serial.print(tepkoupelna);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhkoupelna);
    Serial.println("  %|");
    Serial.println("|___________________________________|");     
     */
      }else{
      digitalWrite(rkouplena, LOW);
    /*
    Serial.println(" ___________________________________");
    Serial.println("|Technická místnost:               |");
    Serial.print("|Teplota: "); 
    Serial.print(tepkoupelna);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlhkoupelna);
    Serial.println("  %|");
    Serial.println("|___________________________________|");
    */
      }
      }
     // delay(5000);
      
/*      
obyvaksend();
pokojsend();
predsinsend();
techsend();
*/
allsend();
} 


void allsend(){
  String sendData = "GET /update?api_key="+ myAPI +"&"+ obyvakFIELD +"="+String(tepobyvak)+"&"+ pokojFIELD +"="+String(teploznice)+"&"+ predsinFIELD +"="+String(teppracovna)+"&"+ techFIELD +"="+String(tepkoupelna);
  espData("AT+CIPMUX=0", 1000, DEBUG); 
  espData("AT+CIPSTART=\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
  //espData("AT+CIPSEND=0," +String(sendData.length()),1000,DEBUG); 
  Serial1.println("AT+CIPSEND=51");
  Serial1.find(">"); 
  Serial1.println(sendData);
  espData("AT+CIPCLOSE=0",1000,DEBUG);
}
/*
void obyvaksend(){
  String sendData = "GET /update?api_key="+ myAPI +"&"+ obyvakFIELD +"="+String(tepobyvak);
  espData("AT+CIPMUX=0", 1000, DEBUG); 
  espData("AT+CIPSTART=\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
  //espData("AT+CIPSEND=0," +String(sendData.length()),1000,DEBUG); 
  Serial1.println("AT+CIPSEND=51");
  Serial1.find(">"); 
  Serial1.println(sendData);
  espData("AT+CIPCLOSE=0",1000,DEBUG);
}
void pokojsend(){
  String sendData = "GET /update?api_key="+ myAPI +"&"+ pokojFIELD +"="+String(teploznice);
  espData("AT+CIPMUX=0", 1000, DEBUG); 
  espData("AT+CIPSTART=\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
  //espData("AT+CIPSEND=0," +String(sendData.length()),1000,DEBUG); 
  Serial1.println("AT+CIPSEND=51");
  Serial1.find(">"); 
  Serial1.println(sendData);
  espData("AT+CIPCLOSE=0",1000,DEBUG);
}
void predsinsend(){
  String sendData = "GET /update?api_key="+ myAPI +"&"+ predsinFIELD +"="+String(teppracovna);
  espData("AT+CIPMUX=0", 1000, DEBUG); 
  espData("AT+CIPSTART=\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
  //espData("AT+CIPSEND=0," +String(sendData.length()),1000,DEBUG); 
  Serial1.println("AT+CIPSEND=51");
  Serial1.find(">"); 
  Serial1.println(sendData);
  espData("AT+CIPCLOSE=0",1000,DEBUG);
}
void techsend(){
  String sendData = "GET /update?api_key="+ myAPI +"&"+ techFIELD +"="+String(tepkoupelna);
  espData("AT+CIPMUX=0", 1000, DEBUG); 
  espData("AT+CIPSTART=\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
  //espData("AT+CIPSEND=0," +String(sendData.length()),1000,DEBUG); 
  Serial1.println("AT+CIPSEND=51");
  Serial1.find(">"); 
  Serial1.println(sendData);
  espData("AT+CIPCLOSE=0",1000,DEBUG);
}
*/




String espData(String command, const int timeout, boolean debug)
{
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");
  String response = "";
  Serial1.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
    Serial.print(response);
  return response;
}
