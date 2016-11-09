// this example is public domain.
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"
#include <util/delay.h>

//Pins for the Olimexino-328

///////////////////////Temperatura////////////////////////////////

int thermoDO = 12;
int thermoCS = 11;
int thermoCLK = 13;

//////////////////////////////////////////////////////////////////

////////////////////Corriente/////////////////////////////////////

int analogPin=0; 
int analogPin1=1; 

int val =0; 
int valor =0;
int promedio=0; 

unsigned long previousMillis = 0;      // will store last time LED was updated 
const long interval = 1;            // interval at which to blink (milliseconds) 
const long a = interval/20;      // 20 muestreos de señal  

/////////////////////////////////////////////////////////////////


MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(115200);





unsigned long previousMillis = 0;      // will store last time LED was updated 
const long interval = 1;            // interval at which to blink (milliseconds) 
const long a = interval/20;      // 20 muestreos de señal 



  
  Serial.println("Adquisicion de datos 1");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
 


///////////////////////// Adquisición corriente /////////////////////////////////////

for (int w=0;w<51;w++)
{
   unsigned long currentMillis = millis(); 

   unsigned long muestreo = 0; 


      if (currentMillis - previousMillis <= interval) 
    { 

      for (int i=1;i<=20;i++) 
             { 
 
         muestreo= i*a+currentMillis; 

         if (currentMillis = muestreo){ 

      val = analogRead(analogPin) - analogRead(analogPin1); 
      
  //    Serial.print("val = "); 
  //    Serial.println(val); 
valor= valor+val;   //acumula los valores 
      

      //  Serial.print("valor "); 
      //  Serial.println(valor); 
                  }     
             } 
      } 

else { 
        promedio=valor/20; 
//         Serial.print("promedio "); 
 //        Serial.println(promedio); 
         valor=0; 
   int corriente = (promedio + 4.11)/8.15; 

        Serial.print("Corriente = "); 
         Serial.println(corriente); 
   previousMillis = currentMillis; 
} 


}
////////////////////////////////////////////////////////////////////////////////////////////////////////


   Serial.print ("C = "); 
   double temp=thermocouple.readCelsius();
   Serial.println
   (temp);
  // Serial.print("F = ");
  // Serial.println(thermocouple.readFarenheit()); 
   _delay_ms(1000);
}
