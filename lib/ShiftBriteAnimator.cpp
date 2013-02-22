class ShiftBriteAnimator {
public:
  LED color;

  ShiftBriteAnimator(ShiftBriteShield *s) {
    shield = s;
    color.set(255,255,255);
  }

  void clear(){
    shield->clear();
  }

  void powerUp(int time){
    clear();
    for (int i = 0; i < NUM_LEDS; i++) {
      shield->lights[i].set(color);
      shield->draw();
      delay(500);
    }
  }

private:
  ShiftBriteShield *shield;
};