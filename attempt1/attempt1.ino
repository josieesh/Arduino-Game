#include <Arduino.h>

volatile double sensorValue = 0;
int interruptPin = 13;
int pin5 = 5;
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
  //delay(1000);
  DDRD = B11111111;
  DDRB = B111111; 
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
  digitalWrite (playerY, LOW);
  delay (500);
}

void downDude(){
  digitalWrite (playerY, HIGH);
  playerY --;
  digitalWrite (playerY, LOW);
  delay(500);
}

void resetDude() {
  PORTD = B11111111;
  while (playerY != 0)
  {
      delay(500);
  digitalWrite (playerY, LOW);
  playerY --;
  digitalWrite (playerY, HIGH);
  }
}

void moveObstacle() {
  //move all obstacle LEDs by 1 x-coordinate to the left
  //ie decrement x-coordinate of all obstacle LEDs
  xCoord --;
  PORTB = B100000;
  digitalWrite(xCoord+6, HIGH);
}

bool checkForFail (Obstacle thing){
  int height = thing.getHeight();
  PORTB = B100000;
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
    
  if (playerY <= height)
    return true;
  else
    return false;
}

void createObstacle(Obstacle thing) {

  PORTB = B100000;
  switch (thing.getHeight()){
  case 2:
    PORTD = B10111110;
    xCoord =6;
    yCoord=2;
    break;
  case 3:
    PORTD = B01111110;
    xCoord =6;
    yCoord=3;
    break;
  case 4:
    PORTD = B00111110;
    xCoord =6;
    yCoord=4;
    break;
  }

  delay(500);
}

void loop() {
  while (!digitalRead(pin5));

  Obstacle thing;
  //digitalWrite(interruptPin, LOW);
  digitalWrite (interruptPin, HIGH);
  createObstacle(thing);
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
  //delay (500);
  bool fail = checkForFail(thing);
  if (fail){
      digitalWrite (interruptPin, LOW);
  }
  //digitalWrite (interruptPin, LOW);
  
  while (fail && !digitalRead(pin5))
  {
     //INFINTE LOOP FOR WHEN GAME IS OVER
  }

  resetDude(); 
  delay (100);  
}

