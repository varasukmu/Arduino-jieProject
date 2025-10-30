// กำหนดขาสำหรับปุ่มและสี RGB
const int BTN_R = 4; // ปุ่มสำหรับสีแดง
const int BTN_G = 5; // ปุ่มสำหรับสีเขียว
const int BTN_B = 6; // ปุ่มสำหรับสีน้ำเงิน

const int LED_R = 8; // LED ขาสีแดง
const int LED_G = 9; // LED ขาสีเขียว
const int LED_B = 10; // LED ขาสีน้ำเงิน

// ตัวแปรสำหรับสถานะไฟ LED (เริ่มต้นเป็น LOW หรือ OFF)
int ledStateR = LOW;
int ledStateG = LOW;
int ledStateB = LOW;

// ตัวแปรสำหรับสถานะปุ่ม (ใช้ในการตรวจจับการกด/ปล่อย หรือ Edge Detection)
int lastButtonStateR = HIGH;
int lastButtonStateG = HIGH;
int lastButtonStateB = HIGH;

void setup()
{
  // กำหนดขาปุ่มเป็น INPUT_PULLUP (ต่อปุ่มกับ GND)
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_G, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);

  // กำหนดขา LED เป็น OUTPUT
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  // กำหนดสถานะเริ่มต้นของไฟ LED
  digitalWrite(LED_R, ledStateR);
  digitalWrite(LED_G, ledStateG);
  digitalWrite(LED_B, ledStateB);
}

void loop()
{
  // ------------------------------------
  // Funtion สำหรับ สีแดง (Red)
  // ------------------------------------
  int currentButtonStateR = digitalRead(BTN_R);
  if (currentButtonStateR != lastButtonStateR) {
    if (currentButtonStateR == LOW) {
      // สลับสถานะ LED
      ledStateR = !ledStateR; // ! คือการกลับค่า (HIGH เป็น LOW, LOW เป็น HIGH)
      digitalWrite(LED_R, ledStateR);
    }
    // อัพเดทสถานะปุ่มที่แล้ว
    lastButtonStateR = currentButtonStateR;
  }

  // ------------------------------------
  // Funtion สำหรับ สีเขียว (Green)
  // ------------------------------------
  int currentButtonStateG = digitalRead(BTN_G);

  if (currentButtonStateG != lastButtonStateG) {
    if (currentButtonStateG == LOW) {
      ledStateG = !ledStateG;
      digitalWrite(LED_G, ledStateG);
    }
    lastButtonStateG = currentButtonStateG;
  }

  // ------------------------------------
  // Funtion สำหรับ สีน้ำเงิน (Blue)
  // ------------------------------------
  int currentButtonStateB = digitalRead(BTN_B);

  if (currentButtonStateB != lastButtonStateB) {
    if (currentButtonStateB == LOW) {
      ledStateB = !ledStateB;
      digitalWrite(LED_B, ledStateB);
    }
    lastButtonStateB = currentButtonStateB;
  }

  // ดีเลย์เล็กน้อยสำหรับ Debounce
  delay(50);
}
