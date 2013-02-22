class ShiftBriteAnimator {
public:
  LED color;
  int time;

  ShiftBriteAnimator(ShiftBriteShield *s) {
    shield = s;
    length = shield->ledsCount();
    color.set(128, 0, 0);
    time = 1000;
  }

  void clear(){
    shield->clear();
  }

  void fill(int startAt = 0, int endAt = NULL, bool forwards = true) {
    if (endAt == NULL) endAt = length;

    int i = startAt;
    while (true) {
      shield->set(i,color);
      shield->draw();

      if (i == endAt) break;
      i = moveIndex(i, forwards);

      delay(msPerLed());
    }
  }

private:
  int length;
  ShiftBriteShield *shield;

  int msPerLed() {
    return time / length;
  }

  int moveIndex(int i, bool forwards) {
    if (forwards) {
      i++;
      if (i >= length) i = 0;
    } else {
      i--;
      if (i < 0) i = length - 1;
    }
    return i;
  }
};