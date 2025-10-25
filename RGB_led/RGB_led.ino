const int red = 7;
const int green = 8;
const int blue = 9;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  setLight(1, 1, 1);
  setLight(1, 1, 0);
  setLight(1, 0, 1);
  setLight(1, 0, 0);
  setLight(0, 1, 1);
  setLight(0, 1, 0);
  setLight(0, 0, 1);
  setLight(0, 0, 0);
}

void setLight(int r, int g, int b) {
  digitalWrite(red, r);
  digitalWrite(green, g);
  digitalWrite(blue, b);
  delay(1000);
}
