#define DEBUG true
String mySSID = "F1_2.4";       // WiFi SSID
String myPWD = "pricna2235"; // WiFi Password
String myAPI = "ZG57XJ27ZQT2E2B9";   // API Key
String myHOST = "184.106.153.149";
String myPORT = "80";
String myFIELD = "field1"; 
String odesilanaHodnota = "2";
void setup() {
  
  Serial.begin(9600);
  Serial1.begin(115200);

  espData("AT+RST", 1000, DEBUG);                      //Reset the ESP8266 module
  espData("AT+CWMODE=1", 1000, DEBUG);                 //Set the ESP mode as station mode
  espData("AT+CWJAP=\""+ mySSID +"\",\""+ myPWD +"\"", 1000, DEBUG);   //Connect to WiFi network
  espData("AT+CIFSR", 1000, DEBUG);
  //delay(1000);
}

void loop() {

esp8266();
 
} 
void esp8266(){
  String sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD +"="+String(odesilanaHodnota);
  espData("AT+CIPMUX=0", 1000, DEBUG); 
  espData("AT+CIPSTART=\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
  //espData("AT+CIPSEND=0," +String(sendData.length()),1000,DEBUG); 
  Serial1.println("AT+CIPSEND=51");
  Serial1.find(">"); 
  Serial1.println(sendData);
  espData("AT+CIPCLOSE=0",1000,DEBUG);
}



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
