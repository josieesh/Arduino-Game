#include <Arduino.h>

volatile double sensorValue = 0;
int interruptPin = 2;
double threshold =0;
int xCoord;
int yCoord;
int playerY = 0;
int decoder0 = 6;
int decoder1 = 7;

class Obstacle {
  private:
    int height;
    double interval;

  public:
    Obstacle();
    void setHeight();
    void setInterval();
    int getHeight();
    double getInterval();
};

Obstacle::Obstacle() {
  setHeight();
  setInterval();
  
}

void Obstacle::setHeight() {
  height = (int)random(3)+2;
}

int Obstacle::getHeight() {
  return height;
}

void Obstacle::setInterval() {
  interval = ((double)(random(200)+100))/100.0;
}

double Obstacle::getInterval() {
  return interval;
};

void setup() {
  delay(1000);
  threshold = analogRead(A0);
  DDRD = B11111111;
  DDRB = B111111;    
}

//interrupt does not work on analog in???
void readMic () {
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue > threshold) {
    if (sensorValue < threshold +10) {
      //jumpDude(2)
      //obstacle x-coordinate ++
      //hold jump
      //obstacle x-coordinate ++
      //come back down
    }
    else if(sensorValue < threshold +20) {
      //jumpDude(3)
      
    }
    else if(sensorValue <threshold +30) {
      //jumpDude(4)
      //
    }
    else {
      //check if obstacle collides with dude
      //if yes, call game over
      //if not, move object closer to dude
    }
  } 
  delay(500);
}

void jumpDude() {
  digitalWrite (playerY, HIGH);
  playerY ++;
  digitalWrite (playerY + 1, LOW);
  delay (500);
}

void moveObstacle() {
  //move all obstacle LEDs by 1 x-coordinate to the left
  //ie decrement x-coordinate of all obstacle LEDs
  xCoord --;
  PORTB = B000000;
  digitalWrite(xCoord+6, HIGH);
}

bool checkForFail (Obstacle thing){
  int height = thing.getHeight();
  PORTB = B000000;
  switch (height){
  case 2:
  PORTD = B11111100;
  break;
  case 3:
  PORTD = B11111000;
  break;
  case 4:
  PORTD = B11110000;
  break;
}
  jumpDude();
    
  if (playerY <= height)
    return true;
  else
    return false;
}

void createObstacle(Obstacle thing) {

  PORTB = B010000;
  switch (thing.getHeight()){
  case 2:
    PORTD = B10111100;
    //digitalWrite (decoder0, LOW);
    //digitalWrite (decoder1, HIGH);
    xCoord =6;
    yCoord=2;
    break;
  case 3:
    PORTD = B01111100;
    //digitalWrite (decoder0, HIGH);
    //digitalWrite (decoder1, LOW);
    xCoord =6;
    yCoord=3;
    break;
  case 4:
    PORTD = B00111100;
    //digitalWrite (decoder0, LOW);
    //digitalWrite (decoder1, LOW);
    xCoord =6;
    yCoord=4;
    break;
  }
}

void loop() {
  
  Obstacle thing;
  createObstacle(thing);
  delay(500);
  for (int i = 3; i >= 0; i--){
    delay(500);
    moveObstacle();
    jumpDude();
  }
  delay (500);
  bool fail = checkForFail(thing);
  if (fail){
    //DDRD = B11111111;
    //DDRB = B111111; 
  }

  playerY = 0;
  
}

