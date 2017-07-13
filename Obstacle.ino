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
}
