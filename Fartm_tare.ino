const int hallSensorPin = A0;  // Hall-effektsensorn ansluts till A0

const float wheelRadius = 0.16;  // Hjulets radie i meter, som man kan ändra beroende på hjul
const float wheelOmkrets = wheelRadius * 2 * 3.14; // Hjulets omkrets räknas ut beroende på radien
int revolutions = 0;  // Antal varv räknas 
int tempRevolutions = 0; // variabel som senare används för att räkna ut hur många varv hjulet har snurrat under en viss tid
int timeCheck; // variabel som tar en viss tidspunkt
int timeCheck2; // -||-
bool bool1 = false; // Boolean som används för att starta if sats utifrån en annan if sats 
bool bool2 = false; // -||-
int kmph = 0; // integer som används som output


void setup() { 
  Serial.begin(9600);  // Startar serial monitorn på 9600 baud 
  pinMode(hallSensorPin, INPUT);  // Anger Hall-effektsensorn som input 
}

void loop() {
  Serial.print(analogRead(hallSensorPin)); // visar värdet på magnetstyrkan i serial monitorn som hall effect sensorn snappar upp 
  Serial.print("   avstånd färdats = " + String(revolutions * wheelOmkrets) + "    "); // Visar hur långt man har färdats i meter totalt med valt hjul genom att räkan ut omkrets ggr antal varv
  Serial.println("KM per H:  " + String(kmph)); // Visar medelhastigheten i km/h under en 5 sekunders period


  if (analogRead(hallSensorPin) <   513  && bool1 == false ) { // if sats som gör så att detektorn inte mäter flera gånger samma varv
    bool1 = true; // boolean blir true så att if satsen inte börjar om direkt igen 
    timeCheck = millis(); // timecheck får värdet av millis (funktion som håller koll på tid i millisekunder) just då 
    revolutions++; // antalet varv ökar med 1 
  }

  if (millis() - timeCheck > 100) { // När det har gått 1 hundradelssekund blir bool1 false och if satsen ovanför kan börja om igen 
    bool1 = false;

  }

  if (bool2 == false) { // En av if satserna för att räkna ut medelhastigheten under 5 sek
    bool2 = true; // bool2 blir true så att if satsen inte börjar om igen direkt 
    tempRevolutions = revolutions; // tempRevolutions tilldelas revolutions 
    timeCheck2 = millis(); // timecheck2 tilldellas millis just då
    

  }

  if (millis() - timeCheck2 > 5000 && bool2 == true) { // efter att det har gått 5 sekunder sedan timeCheck fick sitt värde 
    bool2 = false; // bool2 blir false så att if satsen ovan kan börja om igen 
    int avstand = wheelOmkrets * (revolutions - tempRevolutions); // integern avstånd introduceras och räknas ut genom att ta omkretsen på valt hjul och ggrar det med revolutions - temprovlutions som ger oss antal varv under den 5 sekundersperioden
    kmph = 3.6 * avstand / 5; // km/h räknas ut genom att ta formeln för meter per sekund och ggra den med 3.6 alltså avståndet delat med tiden 
    

  }
}
