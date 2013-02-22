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
    if (endAt == NULL) {
      endAt = length;
    }

    int i = startAt;
    while (i != endAt ) {
      shield->set(i,color);

      i = moveIndex(i, forwards);

      delay(msPerLed());
    }
  }

  void chase(){
    for (int i = 0; i < length; i++) {
      clear();
      shield->set(i, color);
      delay(msPerLed());
    }
  }

private:
  int length;
  ShiftBriteShield *shield;


  int msPerLed() {
    if (length == 0) return 0;
    return time / length;
  }

  int moveIndex(int i, bool forwards) {
    if (forwards) {
      i++;
      if (i > length) i = 0;
    } else {
      i--;
      if (i < 0) i = length - 1;
    }
    return i;
  }
};