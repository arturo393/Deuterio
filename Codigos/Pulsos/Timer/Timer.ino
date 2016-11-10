/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
*/


const int timer2OutPin = 3;
const int timer0OutPin = 9;
const int pulsetrainPin = 11;
const  int gatePin = 12;

int sensorValue0 = 0;        // value read from the pot
int sensorValue1 = 0;        // value read from the pot

int outputValue0 = 0;   
int outputValue1 = 0;   

  // variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;  
// value output to the PWM (analog out)

double freq  = 0;
int incomingByte;
int duty;
float offset;
float currentValue;
bool gate; //activate/desactivate pulse modulation
bool signal_on; //activate/desactivate complete signal
bool freq_on; // activate/desactivate frequency variator
float freq_val; // frequecy value
int preescaler;
int temp;

void setup(){
  
  // enable/disable low frecuency gate
  pinMode(gatePin, INPUT);
  gate = false;
  signal_on = true;
  freq_on = false;
  

  
  pinMode(3, OUTPUT); // signal with variable duty cicle
  pinMode(11, OUTPUT);
  
 /* On the Arduino Duemilanove, these values yield:
=======

>>>>>>> a7be6d13adde10e4f453dd200d26b073805eca5e

    Output A frequency: 16 MHz / 64 / (180+1) / 2 = 690.6Hz
    Output A duty cycle: 50%
    Output B frequency: 16 MHz / 64 / (180+1) = 1381.2Hz
    Output B duty cycle: (50+1) / (180+1) = 28.2% 
*/
// TIMER 0
/* pinMode(6, OUTPUT);  // output A 
 pinMode(5, OUTPUT); // output B
 
  TCCR0A = _BV(COM0A0) | _BV(WGM01);
  TCCR0B = _BV(CS00) | _BV(CS02) ;
  OCR0A = 200;
  OCR0B = OCR0A*0.5;
 TIMSK0 = _BV(OCIE0A);
*/
cli();//stop interrupts
sei();//allow interrupts
Serial.begin(9600);


}//end setup

ISR(TIMER0_COMPA_vect){//timer0 
TCCR2A ^=  (1 << COM2A0) | (1 << COM2B1);
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
}
  
ISR(TIMER2_COMPA_vect){//timer1 interrupt 8kHz toggles pin 9
}


// Variables will change :
int pulseState = LOW;             // ledState used to set the LED
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change :
long interval = 3000;           // interval at which to blink (milliseconds)


void loop(){

  
  // Analog sensor for pot
  sensorValue0 = analogRead(A0);            
  sensorValue1 = analogRead(A1);            
  
  // map it to the range of the analog out:
  outputValue0 = map(sensorValue0, 0, 1023, 30, 220);  
  outputValue1 = map(sensorValue1, 0, 1023, 0,4000 );  
  
    /* Preescaler value
  _CS22 _CS21 _CS20 
   0      0    0      no clock
   0      0    1      no prescaling
   0      1    0      16 MHz / 8 
   0      1    1      16 MHz / 32
   1      0    0      16 MHz / 64
   1      0    1      16 MHz / 128 
   1      1    1      16 MHz / 256 
   1      1    1      16 MHz / 1024
  */ 
  
    if(digitalRead(gatePin) == true){
    signal_on = true;
   TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
   
  
   preescaler = 1; // 1 - 8 - 32 - 64 - 128 - 256
   
   if (preescaler == 1 ) /* 8 [MHz] Khz - 62.7 [KHz] */
   TCCR2B = _BV(WGM22) | _BV(CS20); /

  if (preescaler == 8 ) /* 182.7 [KHz] - 2.56 [KHz] */
  TCCR2B = _BV(WGM22) | _BV(CS21 ); 
 
  if (preescaler == 32 ) /* 250 Khz - 1.92 [KHz] */
  TCCR2B = _BV(WGM22) | _BV(CS21 ) | _BV(CS20);

  if (preescaler == 64 ) /* 125 [KHz]- 980 [Hz] */
  TCCR2B = _BV(WGM22) | _BV(CS22);

  if (preescaler == 128 ) /*  62.5[KHz] - 490 [Hz]*/
  TCCR2B = _BV(WGM22) | _BV(CS22)| _BV(CS20);
 
  if (preescaler == 256 ) /*  7[KHz] - 61.2 [Hz]*/
  TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS21) | _BV(CS20); 

   
}else{
    signal_on = false;
    TCCR2A = 0;
  }
  
  /////////////////////////////////////////////////////////////////
  // Ajsute de frecuencua y ciclo de trabajo //////////////////////
  /////////////////////////////////////////////////////////////////
  if(freq_on == true){
    OCR2A = outputValue0; // Pulse frecuency
    OCR2B = OCR2A*0.;   // Pulse duty clicle (50%)
    } 
    else { // fixed value
      /* Frencuency Set */
      freq_val = 10000000000;
      temp = (16000000.0/freq_val-1)/preescaler;
      
      if(temp >=256 ) // out of range
      OCR2A = 254;
      else if (temp <= 0) // out of range
      OCR2A = 1;
      else 
      OCR2A = temp;
      
      /* Duty Cicle */
      OCR2B = OCR2A*0.5;
      }
  /////////////////////////////////////////////////////////////////    
   interval = outputValue1;
  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

//  freq_val= 1600000.0/(8*OCR2A+1);
  Serial.print(OCR2A);
  Serial.print("\t");
  Serial.print(freq_val);
  Serial.println("[hz]");
  
  if (gate == true) {
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      // if the pulse is off turn it on and vice-versa:
      if (pulseState == LOW) {
        pulseState = HIGH;
      } else {
        pulseState = LOW;
      }
      // set the pulse with the pulseState of the variable:
      TCCR2A ^=  (1 << COM2A0) | (1 << COM2B1);
    }
  }
    
}
