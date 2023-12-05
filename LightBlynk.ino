/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL5u0vWG3i4"
#define BLYNK_TEMPLATE_NAME "Light"
#define BLYNK_AUTH_TOKEN "CvARfG_WQeDHMglNx_S9F4fRJsPzX3c9"

char ssid[] = "ssid";  // Your WiFi credentials.
char pass[] = "pass";

#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

float lux = 0;
// WidgetLED light(V0);

#define in_servo_Pin D1
// #define out_servo_Pin D2
/////////////////////////Servo

void blynksetup() {

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  delay(1000);
}
void blynkLoop() {
  Blynk.run();                  // Initiates Blynk
  Blynk.virtualWrite(V0, lux);  // Lux
  // lux++;
  Serial.println(lux);
  delay(1000);
}


#include <Wire.h>
#include <BH1750.h>

BH1750 lightSensor;
const int ledPin = D5;
const int fadeDuration = 5000;
unsigned long startTime;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lightSensor.begin();
  pinMode(ledPin, OUTPUT);
  blynksetup();
  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  lux = lightSensor.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  int targetBrightness = map(lux, 0, 10000, 255, 0);
  targetBrightness = constrain(targetBrightness, 0, 255);
  int currentBrightness = analogRead(ledPin);
  fadeLED(currentBrightness, targetBrightness);
  blynkLoop();
}

void fadeLED(int startBrightness, int endBrightness) {
  if (millis() - startTime <= fadeDuration) {
    int elapsedTime = millis() - startTime;
    int brightness = map(elapsedTime, 0, fadeDuration, startBrightness, endBrightness);
    analogWrite(ledPin, brightness);
    delay(50);
  } else {
    analogWrite(ledPin, endBrightness);
    startTime = millis();
  }
}
