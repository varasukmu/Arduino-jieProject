const int BTN = 2;
const int LED = 3;

// Variables to manage the toggle state and button press detection
int ledState = LOW;        // current state of the LED (LOW means off)
int lastButtonState = LOW; // the previous reading from the input pin

void setup()
{
  pinMode(BTN, INPUT_PULLUP); // Use INPUT_PULLUP for a cleaner button read
  pinMode(LED, OUTPUT);
  digitalWrite(LED, ledState); // Initialize LED state
}

void loop()
{
  int currentButtonState = digitalRead(BTN);
  if (currentButtonState != lastButtonState) {
    if (currentButtonState == LOW) {
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(LED, ledState);
    }
  }
  lastButtonState = currentButtonState;
  delay(50); 
}


//const int BTN = 2;
//const int LED = 3;
//
//void setup()
//{
//  pinMode(BTN, INPUT);
//  pinMode(LED, OUTPUT);
//}
//
//void loop()
//{
//  if (digitalRead(BTN) == HIGH) {
//    digitalWrite(LED, HIGH);
//  } else {
//    digitalWrite(LED, LOW);
//  }
//}


//const int BTN = 2;
//const int LED = 3;
//
//bool is_led_on = true;
//
//void setup()
//{
//  pinMode(BTN, INPUT);
//  pinMode(LED, OUTPUT);
//}
//
//void loop()
//{
//  if (digitalRead(BTN) == HIGH) {
//    is_led_on = !is_led_on;
//    delay(100);
//  }
//  
//  if (is_led_on) {
//    digitalWrite(LED, HIGH);
//  } else {
//    digitalWrite(LED, LOW);
//  }
//  delay(5);
//}


//const int BTN = 2;
//const int LED = 3;
//
//bool is_led_on = true;
//
//void setup()
//{
//  pinMode(BTN, INPUT_PULLUP);  // Use internal pull-up resistor
//  pinMode(LED, OUTPUT);
//}
//
//void loop()
//{
//  if (digitalRead(BTN) == LOW) {
//    is_led_on = !is_led_on;
//    delay(100);
//  }
//  
//  if (is_led_on) {
//    digitalWrite(LED, HIGH);
//  } else {
//    digitalWrite(LED, LOW);
//  }
//  delay(5);
//}
