volatile int seconds = 0;
int pin2 = 2; //pin to check for game over
int pin3 = 3; //pin to indicate game start to other arduino
int lightPin = 13; //pin for tricolor light
volatile bool isGameOver = true;

void setup() {
  pinMode(pin2, INPUT);
  pinMode(pin3, OUTPUT);
  pinMode(lightPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin2), gameOver, RISING);
  
  Serial.begin(9600);

  cli(); //disable interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<<CS12) | (1<<CS10); //set frequency to clk/1024
  
  TIMSK1 |= (7<<0); //enables OCR interrupts
  OCR1A = 15625;

  sei(); //enable interrupts

  digitalWrite(pin3, LOW);
  while(!Serial.available());
}

ISR (TIMER1_COMPA_vect) {
  seconds ++;
  TCNT1 = 0;
}


void loop() {
  digitalWrite(pin3, HIGH);
  newDelay(500);
  
  if(!isGameOver){
    Serial.println(newMillis());
    //delay a bit between prints
    newDelay(100);
  }
  else {
    digitalWrite(lightPin, HIGH);
    Serial.println("Game Over!");
    digitalWrite(pin3, LOW);
    seconds = 0;
    TCNT1 = 0; //reset timer to 0
    TCCR1B = 0; //stop timer
    cli();
    
    
    while(isGameOver) {
      if(digitalRead(pin2)){
        sei();
      }
    }
    TCCR1B |= (1<<CS12) | (1<<CS10); //reset timer upon exit from infinite loop
  }  
}


double newMillis(){

  //disabled interrupts while reading from timer to avoid getting inconsistent values
  cli();
  
  double t = TCNT1;
  
  double millisec = (seconds + t/15625)*1000;
  //Serial.println(seconds);
  //Serial.println(millisec);

  //restart interrupts
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

void gameOver() {
  if(!isGameOver) {
    isGameOver = true;
  }
  else {
    isGameOver = false;
  }
}

