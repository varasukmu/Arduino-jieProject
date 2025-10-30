// *** สมมติว่าได้ประกาศค่าคงที่เหล่านี้ไว้ด้านนอกแล้ว (เช่น #define SERIES_RESISTOR 10000) ***
// #define SERIES_RESISTOR 10000
// #define THERMISTOR_NOMINAL 10000
// #define TEMPERATURE_NOMINAL 25
// #define B_COEFFICIENT 3950
// #define ADC_MAX 1023.0

void setup() {
  Serial.begin(9600); // เริ่มต้น Serial Monitor
}

void loop() {
  int sensorValue = analogRead(A0); // อ่านค่าเซนเซอร์

  // 1. คำนวณความต้านทานของ Thermistor
  float resistance = 10000.0 / (1023.0 / sensorValue - 1.0); // ใช้ค่า 10k เป็นตัวอย่าง

  // 2. ใช้สูตร Steinhart-Hart คำนวณอุณหภูมิ (แปลงเป็น Kelvin แล้วลบ 273.15 เพื่อให้เป็น Celsius)
  float steinhart;
  steinhart = resistance / 10000.0; // R / R0 (สมมติ R0 = 10k)
  steinhart = log(steinhart);
  steinhart /= 3950.0; // หารด้วย B-coefficient (สมมติ B = 3950)
  steinhart += 1.0 / (25.0 + 273.15); // + 1/T0 (สมมติ T0 = 25C)
  steinhart = 1.0 / steinhart;

  float temperatureC = steinhart - 273.15; // T (Kelvin) -> T (Celsius)
  
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  
  delay(1000); // หน่วงเวลา 1 วินาที
}
