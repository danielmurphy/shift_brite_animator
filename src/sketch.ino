#define NUM_LEDS 9

#include "../lib/LED.cpp"
#include "../lib/ShiftBriteShield.cpp"
#include "../lib/ShiftBriteAnimator.cpp"

#define DATA_PIN 11 // DI
#define LATCH_PIN 9 // LI
#define ENABLE_PIN 10 // EI
#define CLOCK_PIN 13 // CI


ShiftBriteShield shield (DATA_PIN, LATCH_PIN, ENABLE_PIN, CLOCK_PIN);
ShiftBriteAnimator animator(&shield);

void setup() {
  // LED redLed(255, 0, 0);
  // LED greenLed(0, 255, 0);
  // LED blueLed(0, 0, 255);

  // shield.lights[0] = blueLed;
  // shield.draw();
  // delay(500);
  // animator.clear();
  // animator.powerUp(1000);
  // animator.powerDown(1000);

  animator.clear();
  animator.fill(8, 0, false);

}


void loop() {
  // for (int i = 0; i < NUM_LEDS; i++) {
  //   shield.clear();
  //   shield.lights[i] = blueLed;
  //   shield.draw();
  //   delay(200);
  // }

  // for (int i = NUM_LEDS - 1; i >= 0; i--) {
  //   shield.clear();
  //   shield.lights[i] = greenLed;
  //   shield.draw();
  //   delay(200);
  // }
  // Serial.println(red[0]);

  // shield.draw([0][])
}