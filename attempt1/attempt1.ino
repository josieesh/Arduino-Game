#include <Arduino.h>

volatile double sensorValue = 0;
int interruptPin = 13;
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
  DDRD = B11111111;
  DDRB = B111111; 

  digitalWrite (interruptPin, HIGH);
}

//interrupt does not work on analog in???
int readMic () {
  sensorValue = 1000.0 / analogRead(A0);
  Serial.println(sensorValue);
    if (sensorValue >= 2 && sensorValue < 3) {
        return 1;
    }
    else if(sensorValue >= 3 && sensorValue < 4) {
      return 2;
    }
    else if(sensorValue >= 4 && sensorValue <5) {
      return 3;
    }
    else if (sensorValue >= 5) {
      return 4;
    }
    else
    {
      return 0;
    }
}

void jumpDude() {
  digitalWrite (playerY, HIGH);
  playerY ++;
  digitalWrite (playerY + 1, LOW);
  delay (500);
}

void downDude(){
  digitalWrite (playerY + 1, HIGH);
  playerY --;
  digitalWrite (playerY, LOW);
  delay(500);
}

void resetDude() {
  PORTD = B11111111;
  while (playerY != 0)
  {
      delay(500);
      digitalWrite (playerY + 1, HIGH);
      playerY --;
      digitalWrite (playerY, LOW);
  }
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
  //jumpDude();
    
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
  int jump = readMic();

  while (jump == 0 && xCoord > 1)
  {
    delay(500);
    moveObstacle();
    jump = readMic();
  }
  if (jump >= 1){
    for (int i = jump; i >= 0; i--){
    delay(500);
    moveObstacle();
    jumpDude();
    }
  }
  delay (500);
  bool fail = checkForFail(thing);
  if (fail){
      //PORTB = B111111; //turn on all the lights and trigger interrupt pin
      //PORTD = B00000000;
      digitalWrite (interruptPin, HIGH);
      //delay(500);
      //digitalWrite (interruptPin, LOW);
  }

  resetDude();
  
}

