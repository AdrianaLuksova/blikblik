#include <Arduino.h>             
#define IR_USE_AVR_TIMER 1      
#include <IRremote.hpp>          


#define IR_RECEIVE_PIN 12       


#define RED 3208707840           
#define BLUE 3091726080        
#define GREEN 3158572800       


#define blue 9                  
#define red 6                   
#define green 5                  

// Definice pinů pro LED bar a IR kódů pro čísla 0-9
int bar[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};     // Pole pinů pro LED bar
unsigned long codes[] = {                         // Pole IR kódů pro čísla 0-9
    3910598400, // 0
    4077715200, // 1
    3877175040, // 2
    2707357440, // 3
    4144561920, // 4
    3810328320, // 5
    2774204160, // 6
    3175284480, // 7
    2907897600, // 8
    3041591040, // 9
};


int codesSize = sizeof(codes) / sizeof(codes[0]);

// Proměnná pro uchovávání řetězce čísla
String stringNum = "";         

// Funkce pro nastavení RGB hodnot
void setRGB(int redVal, int greenVal, int blueVal) {
  analogWrite(red, redVal);    
  analogWrite(green, greenVal);
  analogWrite(blue, blueVal);  
}

void setup() {
  pinMode(red, OUTPUT);       
  pinMode(green, OUTPUT);    
  pinMode(blue, OUTPUT);      
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
  
  Serial.begin(9600);          
}

void loop() {
  if (IrReceiver.decode()) {   // Kontrola, zda byl přijat signál z IR dálkového ovládání
    unsigned long receivedValue = IrReceiver.decodedIRData.decodedRawData; // Získání přijaté hodnoty
    Serial.println(receivedValue); // Výpis přijaté hodnoty na sériový monitor
    
    for (int i = 0; i < 10; i++) { 
      if (receivedValue == codes[i])
        stringNum += String(i).c_str(); // Přidání čísla do řetězce
    }
    
    if (receivedValue == RED) { // Pokud je přijat kód pro červenou barvu
      int intNum = stringNum.toInt(); 
      stringNum = ""; // Vyprázdnění řetězce
      if (intNum >= 0 && intNum <= 255) { // Kontrola, zda je číslo v intervalu 0-255
        Serial.print("Zadaná hodnota: ");
        Serial.println(intNum); // Výpis hodnoty na sériový monitor
        analogWrite(red, intNum); 
      } else {
        Serial.println("Zadané číslo není v intervalu 0-255."); 
      }
    }

    if (receivedValue == GREEN) { // Pokud je přijat kód pro zelenou barvu
      int intNum = stringNum.toInt(); 
      stringNum = ""; // Vyprázdnění řetězce
      if (intNum >= 0 && intNum <= 255) { // Kontrola, zda je číslo v intervalu 0-255
        Serial.print("Zadaná hodnota: ");
        Serial.println(intNum); // Výpis hodnoty na sériový monitor
        analogWrite(green, intNum); 
      } else {
        Serial.println("Zadané číslo není v intervalu 0-255."); 
      }
    }

    if (receivedValue == BLUE) { // Pokud je přijat kód pro modrou barvu
      int intNum = stringNum.toInt(); 
      stringNum = ""; // Vyprázdnění řetězce
      if (intNum >= 0 && intNum <= 255) { // Kontrola, zda je číslo v intervalu 0-255
        Serial.print("Zadaná hodnota: ");
        Serial.println(intNum); // Výpis hodnoty na sériový monitor
        analogWrite(blue, intNum);
      } else {
        Serial.println("Zadané číslo není v intervalu 0-255."); 
      }
    }

    IrReceiver.resume(); 
  }
}