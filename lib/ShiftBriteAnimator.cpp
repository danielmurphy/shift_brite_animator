class ShiftBriteAnimator {
public:
  LED color;
  int numLeds, time;

  ShiftBriteAnimator(ShiftBriteShield *s, int l = NUM_LEDS) {
    shield = s;
    numLeds = l;
    color.set(255,0,0);
    time = 1000;
  }

  void clear(){
    shield->clear();
  }

  void fill(int startAt = 0, int endAt = NUM_LEDS - 1, bool forwards = true) {
    int i = startAt;

    while (true) {
      shield->lights[i].set(color);
      shield->draw();
      delay(time/numLeds);

      if (i == endAt) {
        break;
      }

      if (forwards) {
        i++;
        if (i >= NUM_LEDS) {
          i = 0;
        }
      } else {
        i--;
        if (i < 0) {
          i = NUM_LEDS - 1;
        }
      }
    }
  }

  void powerUp(int time){
    for (int i = 0; i < numLeds; i++) {
      shield->lights[i].set(color);
    }
  }

  void powerDown(int time){
  }

private:
  ShiftBriteShield *shield;
};