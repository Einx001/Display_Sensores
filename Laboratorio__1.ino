//Trabajo realizado por: Angel David Achinco y Arturo Restrepo Ruiz

#include <LiquidCrystal.h>
#include "DHTStable.h"
#include "AsyncTaskLib.h"


DHTStable DHT;

#define DHT11_PIN       22
#define LED_RED 19
#define LED_GREEN 20
#define LED_BLUE 21


void medirTemperatura();
void medirHumedad();

AsyncTask asyncTask7(1000, medirTemperatura);
AsyncTask asyncTask8(2000, medirHumedad);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  asyncTask7.Start();
  asyncTask8.Start();
}

void loop() {
  asyncTask7.Update();
  asyncTask8.Update();
}

void medirTemperatura(){
  int chk = DHT.read11(DHT11_PIN);
    switch (chk)
    {
      case DHTLIB_OK:  
        Serial.print("OK,\t"); 
        break;
      case DHTLIB_ERROR_CHECKSUM: 
        Serial.print("Checksum error,\t"); 
        break;
      case DHTLIB_ERROR_TIMEOUT: 
        Serial.print("Time out error,\t"); 
        break;
      default: 
        Serial.print("Unknown error,\t"); 
        break;
    }
    // DISPLAY DATA
    lcd.clear();
    lcd.setCursor(0,0);
    
    lcd.print("temperatura: ");
    //Serial.print(",\t");
    lcd.println(DHT.getTemperature(), 1);

    if(DHT.getTemperature()>28){
	  digitalWrite(LED_BLUE, LOW);
	  digitalWrite(LED_GREEN, LOW);
          digitalWrite(LED_RED, HIGH);  // turn the LED on (HIGH is the voltage level)
      }else if(DHT.getTemperature()<25){
	  digitalWrite(LED_GREEN, LOW);
	  digitalWrite(LED_RED, LOW);
          digitalWrite(LED_BLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
      }else if(DHT.getTemperature()>25&&DHT.getTemperature()<28){
	  digitalWrite(LED_BLUE, LOW);
	  digitalWrite(LED_RED, LOW);
          digitalWrite(LED_GREEN, HIGH);  // turn the LED on (HIGH is the voltage level) 
      }
  }

  
void medirHumedad(){
  int chk = DHT.read11(DHT11_PIN);
    switch (chk)
    {
      case DHTLIB_OK:  
        Serial.print("OK,\t"); 
        break;
      case DHTLIB_ERROR_CHECKSUM: 
        Serial.print("Checksum error,\t"); 
        break;
      case DHTLIB_ERROR_TIMEOUT: 
        Serial.print("Time out error,\t"); 
        break;
      default: 
        Serial.print("Unknown error,\t"); 
        break;
    }
    // DISPLAY DATA
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("humedad: ");
    lcd.print(DHT.getHumidity(), 1);
    lcd.setCursor(0,1);

  }
