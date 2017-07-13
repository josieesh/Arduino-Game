#include <Arduino.h>
#include <Obstacle.ino>
#include <Player.ino>

volatile double sensorValue = 0;
int interruptPin = 2;
double threshold =0;
int x [3];
int y [4];
int xCoord;
int yCoord;



void setup() {
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), readMic, CHANGE);
  Serial.println("Do not make noise, calibrating threshold value...");
  delay(1000);
  threshold = analogRead(A0);
  Serial.print("Threshold value: ");
  Serial.println(threshold);
  DDRD = B11111110;
  DDRB = B111111;
    
}
void loop() {
  
  /*Obstacle thing;
  Serial.println(thing.getHeight());
  Serial.println("\ninterval:");
  Serial.println(thing.getInterval());

  createObstacle(thing);

  delay(1000);
  moveObstacle();

  delay(1000);
  moveObstacle(); */

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

//interrupt does not work on analog in???
void readMic () {
  sensorValue = analogRead(A0);
}

void jumpDude(int height) {
  //dude led y-coordinate + height
}

void moveObstacle() {
  //move all obstacle LEDs by 1 x-coordinate to the left
  //ie decrement x-coordinate of all obstacle LEDs
  xCoord --;
  Serial.println(xCoord);
  PORTD = B00000000;
  digitalWrite(xCoord+2, HIGH);
  /*if (yCoord ==1) {
    digitalWrite(8, HIGH);
  }
  else if(yCoord ==2) {
    
  } */
  
}

void createObstacle(Obstacle thing) {

  //height of 1:
  if(thing.getHeight() ==1) {
    PORTD = B00100000;
    PORTB = B111110;
    xCoord =3;
    yCoord=1;
  }

  //height of 2:
  else if(thing.getHeight() == 2) {
    PORTD = B00100000;
    PORTB = B111100;
    xCoord = 3;
    yCoord = 2;
  }
  
  //height of 3:
  else {
    PORTD = B00100000;
    PORTB = B111000;
    xCoord = 3;
    yCoord = 3;
  }
  
}

