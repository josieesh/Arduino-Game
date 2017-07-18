volatile int seconds = 0;

void setup() {
  Serial.begin(9600);

  cli(); //disable interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS12) | (1<<CS10); //set frequency to clk/1024
  
  TIMSK1 |= (7<<0); //enables OCR interrupts
  OCR1A = 15625;

  sei(); //enable interrupts
}

ISR (TIMER1_COMPA_vect) {
  Serial.println("Reached 15625");
  seconds ++;
  TCNT1 = 0;
}


void loop() {
  Serial.println(newMillis());
}


double newMillis(){

  //disabled interrupts while reading from timer to avoid getting inconsistent values
  cli();
  
  double t = TCNT1;
  
  double millisec = (seconds + t/15625)*1000;
  //Serial.println(seconds);
  //Serial.println(millisec);

  sei();

  return millisec;
}



void newDelay(int amt) {
  double startTime = newMillis();
  double endTime = newMillis(); 
  while(endTime - startTime < amt) {
    endTime = newMillis();
  }
}

