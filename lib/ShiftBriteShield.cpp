#define DATA_PIN 11 // DI
#define LATCH_PIN 9 // LI
#define ENABLE_PIN 10 // EI
#define CLOCK_PIN 13 // CI


class ShiftBriteShield {
public:
  LED *lights;

  ShiftBriteShield (LED* l, int len, int dp = DATA_PIN, int lp = LATCH_PIN, int ep = ENABLE_PIN, int cp = CLOCK_PIN){
    lights = l;
    length = len;
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

  void set(int index, LED color, bool render = true) {
    lights[index].set(color);
    if (render) draw();
  }

  void clear() {
    for (int i = 0; i < length; i++) {
      lights[i].off();
    }
    draw();
  }

  void draw() {
    for (int i = 0; i < length; i++) {
      sendPacket(B00, lights[i]);
    }

    delayMicroseconds(15);
    digitalWrite(latchPin,HIGH); // latch data into registers
    delayMicroseconds(15);
    digitalWrite(latchPin,LOW);

    for (int i = 0; i < length; i++) sendPacket(B01, lights[i]);
      delayMicroseconds(15);
      digitalWrite(latchPin,HIGH); // latch data into registers
      delayMicroseconds(15);
      digitalWrite(latchPin,LOW);
  }

  int ledsCount(){
    return length;
  }

private:
  int redCommand, greenCommand, blueCommand;
  int dataPin, latchPin, enablePin, clockPin, length;

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