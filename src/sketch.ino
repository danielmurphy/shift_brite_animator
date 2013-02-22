#define DATA_PIN 11 // DI
#define LATCH_PIN 9 // LI
#define ENABLE_PIN 10 // EI
#define CLOCK_PIN 13 // CI

#define NUM_LEDS 9

#define LED_PIN 12

class LED {

public:
  int red, green, blue;
  LED(int r = 0, int g = 0, int b = 0) {
    setColors(r, g, b);
  }

  void set(int r, int g, int b) {
    setColors(r, g, b);
  }

private:
  void setColors(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
  }
};

class ShiftBriteShield {
  int dataPin, latchPin, enablePin, clockPin;
public:

  ShiftBriteShield (int dp, int lp, int ep, int cp){
    dataPin = dp;
    latchPin = lp;
    enablePin = ep;
    clockPin = cp;

    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
    digitalWrite(latchPin, LOW);
    digitalWrite(enablePin, LOW);
  }

  void draw(LED leds[NUM_LEDS]) {
    for (int i = 0; i < NUM_LEDS; i++) {
      sendPacket(B00, leds[i]);
    }

    delayMicroseconds(15);
    digitalWrite(latchPin,HIGH); // latch data into registers
    delayMicroseconds(15);
    digitalWrite(latchPin,LOW);

    for (int i = 0; i < NUM_LEDS; i++) sendPacket(B01, leds[i]);
      delayMicroseconds(15);
      digitalWrite(latchPin,HIGH); // latch data into registers
      delayMicroseconds(15);
      digitalWrite(latchPin,LOW);
  }

private:
  int redCommand, greenCommand, blueCommand;


  void sendPacket(int commandMode, LED led) {
    if (commandMode == B01) {
      redCommand = 120;
      greenCommand = 100;
      blueCommand = 100;
    } else {
      redCommand = led.red;
      greenCommand = led.green;
      blueCommand = led.blue;
    }

    SPDR = commandMode << 6 | blueCommand>>4;
    while(!(SPSR & (1<<SPIF)));
    SPDR = blueCommand<<4 | redCommand>>6;
    while(!(SPSR & (1<<SPIF)));
    SPDR = redCommand << 2 | greenCommand>>8;
    while(!(SPSR & (1<<SPIF)));
    SPDR = greenCommand;
    while(!(SPSR & (1<<SPIF)));
  }
};



ShiftBriteShield shield (DATA_PIN, LATCH_PIN, ENABLE_PIN, CLOCK_PIN);

LED lights[NUM_LEDS];

void setup() {
  LED redLed(255, 0, 0);
  LED greenLed(0, 255, 0);
  LED blueLed(0, 0, 255);

  LED colors[3];
  colors[0] = redLed;
  colors[1] = greenLed;
  colors[2] = blueLed;

  for (int i = 0; i < NUM_LEDS; i++) {
    lights[i] = colors[i % 3];
  }

  shield.draw(lights);
}


void loop() {
  // Serial.println(red[0]);

  // shield.draw([0][])
}