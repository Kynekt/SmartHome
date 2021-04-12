#include "DHT.h"
#define pinDHT 6
#define typDHT22 DHT22  


DHT mojeDHT(pinDHT, typDHT22);

void setup() {
 Serial.begin(9600); 
 mojeDHT.begin();
}

void loop() {
  float tep = mojeDHT.readTemperature();
  float vlh = mojeDHT.readHumidity();
  
  if (isnan(tep) || isnan(vlh)) {
    Serial.println("Chyba při čtení z DHT senzoru!");
      
  } else {

    Serial.println(" ___________________________________");
    Serial.println("|Obývací pokoj:                     |");
    Serial.print("|Teplota: "); 
    Serial.print(tep);
    Serial.print("°C, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlh);
    Serial.println("  %|");
    Serial.println("|___________________________________|");
    
  }
 
 delay(5000);
}
