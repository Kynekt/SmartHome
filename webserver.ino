#define serialCommunicationSpeed 9600
#define DEBUG true      
    
int obyvak1 = 12;
int obyvak2 = 11;
int loznice = 10;
int koupelna = 9;
int pracovna = 8;
int veranda = 7;

void setup()      
{      
  pinMode(obyvak1,OUTPUT);                                 
  pinMode(obyvak2,OUTPUT);                                        
  pinMode(loznice,OUTPUT);
  pinMode(koupelna,OUTPUT);
  pinMode(pracovna,OUTPUT);
  pinMode(veranda,OUTPUT);
        
  digitalWrite(obyvak1,LOW);                        
  digitalWrite(obyvak2,LOW); 
  digitalWrite(loznice,LOW); 
  digitalWrite(koupelna,LOW); 
  digitalWrite(pracovna,LOW); 
  digitalWrite(veranda,LOW);     
  Serial.begin(9600);          
  Serial1.begin(115200);          
  InitWifiModule();                               
}      
void loop(){      
  if(Serial1.available())                                          
  {      
    if(Serial1.find("+IPD,"))                                           
    {      
      delay(1000);                                                        
      int connectionId = Serial1.read()-48;                         
      Serial1.find("pin=");                                              
      int pinNumber = (Serial1.read()-48)*10;                             
      pinNumber = pinNumber + (Serial1.read()-48);                      
      Serial.print("pinnumver: ");
      Serial.print(pinNumber);
      int statusLed =(Serial1.read()-48);                            
      if (pinNumber == 12){
        if (statusLed == 1){
          digitalWrite(obyvak1, HIGH);
          digitalWrite(obyvak2, HIGH);
          }
        if (statusLed == 0){
          digitalWrite(obyvak1, LOW);
          digitalWrite(obyvak2, LOW);
          }
        }
        if (pinNumber == 10){
        if (statusLed == 1){
          digitalWrite(loznice, HIGH);
          }
        if (statusLed == 0){
          digitalWrite(loznice, LOW);
          }
        }
        if (pinNumber == 99){
          pinNumber = pinNumber - 90;
        if (statusLed == 1){
          digitalWrite(koupelna, HIGH);
          }
        if (statusLed == 0){
          digitalWrite(koupelna, LOW);
          }
        }
        if (pinNumber == 98){
          pinNumber = pinNumber - 90;
        if (statusLed == 1){
          digitalWrite(pracovna, HIGH);
          }
        if (statusLed == 0){
          digitalWrite(pracovna, LOW);
          }
        }
        if (pinNumber == 97){
          pinNumber = pinNumber - 90;
        if (statusLed == 1){
          digitalWrite(veranda, HIGH);
          }
        if (statusLed == 0){
          digitalWrite(veranda, LOW);
          }
        }    
      //digitalWrite(pinNumber, statusLed);                               
      Serial.println(connectionId);                                     
      Serial.print(pinNumber);                                           
      Serial.print("      ");                                          
      Serial.println(statusLed);                                         
      String closeCommand = "AT+CIPCLOSE=";                               
      closeCommand+=connectionId;                                       
      closeCommand+="\r\n";                                              
      sendData(closeCommand,1000,DEBUG);                                 
            
    }      
  }      
}      
     
String sendData(String command, const int timeout, boolean debug)      
{      
    String response = "";                                                 
          
    Serial1.print(command);                                              
    long int time = millis();                                             
    while( (time+timeout) > millis())                                     
    {            
      while(Serial1.available())                                         
      {      
        char c = Serial1.read();                                          
        response+=c;                                                      
      }        
    }          
    if(debug)                                                               
    {      
      Serial.print(response);      
    }          
    return response;                                                     
}      
      
void InitWifiModule()      
{      
  sendData("AT+RST\r\n", 2000, DEBUG);                                                       
  //delay(1000);      
  sendData("AT+CWJAP=\"robotika\",\"nasratpanove\"\r\n", 2000, DEBUG);              
  delay (3000);      
  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);                                                  
  delay (1000);      
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                                    
  delay (1000);      
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);                                                   
  delay (1000);      
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);                                             
}   
