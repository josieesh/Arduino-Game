#include <Arduino.h>

volatile double sensorValue = 0;
int interruptPin = 2;
double threshold =0;
int x [3];
int y [4];
int xCoord;
int yCoord;




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
  height = (int)random(3)+1;
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



/*class Player {
  private: 
    int height;

  public: 
    Player(int h);
    void jump(int jumpHeight);
}

Player::Player(int h) {
  height = h;
}

void Player::jump(int jumpHeight) {
  if (jumpHeight == 2) {
    //animate
    //(1,2), (1,3)
    //bring obstacle closer
    //(1,3), (1,4)
    //bring obstacle closer
    //then come back down
  }
  else if(jumpHeight == 3){
    //animate
    //(1,2), (1,3)
    //bring obstacle closer
    //(1,3), (1,4)
    //bring obstacle closer
    //(1,4), (1,5)
    //bring obstacle closer
    //then come back down 
  }
  else if(jumpHeight ==4){
    //animate
    //(1,2), (1,3)
    //bring obstacle closer
    //(1,3), (1,4)
    //bring obstacle closer
    //(1,4), (1,5)
    //bring obstacle closer
    //(1,5), (1,6)
    //bring obstacle closer
    //then come back down 
  }
  else {
    //do nothing ie keep the bottom two lights on
  }
};

*/




void setup() {
  Serial.begin(9600);
  Serial.println("Do not make noise, calibrating threshold value...");
  delay(1000);
  threshold = analogRead(A0);
  Serial.print("Threshold value: ");
  Serial.println(threshold);
  DDRD = B11111110;
  DDRB = B111111;
    
}
void loop() {
  
  Obstacle thing;
  Serial.println(thing.getHeight());
  Serial.println("\ninterval:");
  Serial.println(thing.getInterval());

  createObstacle(thing);
  makeDude();

  delay(5000);
  /*for (int i = 0; i < 5; i ++) {
    moveObstacle();
    delay(500);
  }*/
  

  /*sensorValue = analogRead(A0);
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
  delay(500);*/
}

//interrupt does not work on analog in???
void readMic () {
  sensorValue = analogRead(A0);
}

void makeDude()
{
  Serial.println("dude is made");
  digitalWrite (8, HIGH); //x coord
  digitalWrite (2, LOW); //y coord
}

void jumpDude(int height, Obstacle thing) {
  for (int i = thing.getHeight(); i<= height; i++)
  {
    digitalWrite (yCoord+7, LOW);
  }
}

void moveObstacle() {
  //move all obstacle LEDs by 1 x-coordinate to the left
  //ie decrement x-coordinate of all obstacle LEDs
  xCoord --;
  PORTD = B11111111;
  PORTB = B000000;
  digitalWrite(xCoord+7, HIGH);
  if (yCoord ==1) {
    PORTD = B11111011;
  }
  else if(yCoord ==2) {
    PORTD = B11110011;
  }
  else if(yCoord ==3) {
    PORTD = B11100011;
  }
}

void createObstacle(Obstacle thing) {

  //height of 1:
  if(thing.getHeight() == 1) {
    PORTD = B11111000;
    PORTB = B010000;
    xCoord =5;
    yCoord=1;
  }

  //height of 2:
  else if(thing.getHeight() == 2) {
    PORTD = B11110000;
    PORTB = B010000;
    xCoord = 5;
    yCoord = 2;
  }
  
  //height of 3:
  else {
    PORTD = B11100000;
    PORTB = B010000;
    xCoord = 5;
    yCoord = 3;
  }
  
}

