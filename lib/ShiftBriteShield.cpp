class ShiftBriteShield {
public:
  int dataPin, latchPin, enablePin, clockPin;
  LED lights[NUM_LEDS];

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

  void clear() {
    for (int i = 0; i < NUM_LEDS; i++) {
      lights[i].off();
    }
    draw();
  }

  void draw() {
    for (int i = 0; i < NUM_LEDS; i++) {
      sendPacket(B00, lights[i]);
    }

    delayMicroseconds(15);
    digitalWrite(latchPin,HIGH); // latch data into registers
    delayMicroseconds(15);
    digitalWrite(latchPin,LOW);

    for (int i = 0; i < NUM_LEDS; i++) sendPacket(B01, lights[i]);
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