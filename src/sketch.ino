#define NUM_LEDS 9

#include "../lib/LED.cpp"
#include "../lib/ShiftBriteShield.cpp"
#include "../lib/ShiftBriteAnimator.cpp"

LED lights[NUM_LEDS];
ShiftBriteShield shield (lights, NUM_LEDS);
ShiftBriteAnimator animator(&shield);

void setup() {

}


void loop() {
  animator.fill();
  shield.clear();
  animator.chase();
  shield.clear();
}