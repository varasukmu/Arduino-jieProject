#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "Varaporn";     // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "123456789";  // CHANGE TO YOUR WIFI PASSWORD

const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th";  // CHANGE TO MQTT BROKER'S ADDRESS
//const char MQTT_BROKER_ADRRESS[] = "192.168.0.11";  // CHANGE TO MQTT BROKER'S IP ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "arduino-uno-r4-client";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";              // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";              // CHANGE IT IF REQUIRED, empty if not required

// The MQTT topics that Arduino should publish/subscribe
const char PUBLISH_TOPIC_A[] = "67070159/temp";       // CHANGE IT AS YOU DESIRE
const char PUBLISH_TOPIC_B[] = "67070159/light";       // CHANGE IT AS YOU DESIRE
const char SUBSCRIBE_TOPIC[] = "67070159/venus";  // CHANGE IT AS YOU DESIRE

const int PUBLISH_INTERVAL = 5000;  // 5 seconds


const int red = 7;
const int green = 8;
const int blue = 9;


WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

void setup() {
  Serial.begin(9600);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Arduino UNO R4 - Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  connectToMQTT();


  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

}

void loop() {
  mqtt.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageReceived);

  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino UNO R4 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT() {

//  Temp
  int sensorValue = analogRead(A0); // อ่านค่าเซนเซอร์
  float voltage = sensorValue * (4.7 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100;
  String  temp_str = String(temperatureC);
  
  char messageBufferA[10];
  temp_str.toCharArray(messageBufferA, 10);
  mqtt.publish(PUBLISH_TOPIC_A, messageBufferA);

//  nob
  int potValue = analogRead(A1) / 4 ;
  String pot_str = String(potValue);

  char messageBufferB[10];
  pot_str.toCharArray(messageBufferB, 10);
  mqtt.publish(PUBLISH_TOPIC_B, messageBufferB);


  }
void messageReceived(String &topic, String &payload) {
  Serial.println("Arduino UNO R4 - received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload:");
  Serial.println(payload);

  // 1. แปลงค่า payload (String) ให้เป็นตัวเลขจำนวนเต็ม (int)
  int controlValue = payload.toInt(); 
  
  // 2. ใช้ค่าตัวเลขที่แปลงแล้วในการเปรียบเทียบ
  if (36 <= controlValue && controlValue <= 50)
    setLight( 0, 1, 1); // แดง
  else if (26 <= controlValue && controlValue <= 35)
    setLight( 1, 0, 1); // เขียว
  else if (10 <= controlValue && controlValue <= 25)
    setLight( 1, 1, 0); // น้ำเงิน
  else
    setLight( 1, 1, 1);
}

void setLight(int r, int g, int b) {
   digitalWrite(red, r);
   digitalWrite(green, g);
   digitalWrite(blue, b);
   delay(1000);
}
