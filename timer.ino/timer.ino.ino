#include <LiquidCrystal.h>
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

volatile int ovrflw=0;

void setup() {
  Serial.begin(9600);
  //lcd.begin(16,2);
  //pinMode(2, INPUT);
  
  cli(); //disabled timer interrupts

  TCCR1A = 0; //disable the timer while we set it up
  TCCR1B = 0;
  TCCR1B = (5<<0); //set clock frequency to clk/1024
  TCNT1 = 0; //make sure tnct register starts at 0 when program starts

  TIMSK1 |= (7<<0); //enable interrupts of timer1
  //OCR1A = 65535;
  sei(); //enable timer interrupts
}

/*ISR(TIMER1_COMPA_vect) {
  Serial.println("overflow");
  Serial.println(ovrflw);
  ovrflw++;
}
*/
//overflow fnction to increment the ovrflw global variable so it can be used in the new millis()
ISR(TIMER1_OVF_vect) {
  ovrflw++;
  Serial.print("overflow fnc");
}

void loop() {
  Serial.println("inside loop");
  Serial.println(ovrflw);

  //lcd.setCursor(0,0);  

  while(1) {
    long timerValue = newMillis();
    TCCR1B = 0; //disable timer1 while printing
    //lcd.print(timerValue);
    TCCR1B = B00000101; //reenable timer1 to clock frequency of /1024
  }
  

}



long newMillis(){

  Serial.println("inside newMillis");

  //disabled interrupts while reading from timer to avoid getting inconsistent values
  cli();
  long t = TCNT1;
  Serial.print("t = ");
  Serial.println(t);
  long millisec = ((ovrflw*65535) + t)/15.625;

  Serial.print("millis = ");
  Serial.println(millisec);

  sei();

  return millisec;
}

void newDelay(int amt) {
  long startTime = newMillis();
  long endTime = newMillis(); 
  while(endTime - startTime < amt) {
    endTime = newMillis();
  }
}

