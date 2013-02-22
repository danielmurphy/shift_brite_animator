class LED {

public:
  int red, green, blue;
  LED(int r = 0, int g = 0, int b = 0) {
    setColors(r, g, b);
  }

  void set(int r, int g, int b) {
    setColors(r, g, b);
  }

  void set(LED new_color) {
    setColors(new_color.red, new_color.green, new_color.blue);
  }

  void off(){
    setColors(0,0,0);
  }

private:
  void setColors(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
  }
};