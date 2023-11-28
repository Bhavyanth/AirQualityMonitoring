#include "heltec.h"
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// #define BLYNK_TEMPLATE_ID "TMPL2n0-pWRpd"
// #define BLYNK_TEMPLATE_NAME "AIR Controller"
// #define BLYNK_AUTH_TOKEN "-y3lHJGQtG-veg9ZNIMkX3zaS8F8YcD7"
#define BLYNK_TEMPLATE_ID "TMPL2wXNYo1oR"
#define BLYNK_TEMPLATE_NAME "AIR QUALITY MONITORING"
#define BLYNK_AUTH_TOKEN "wMj5s0BHSvDJ-FrbbHydJ-NxgdvUbW89"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DHT_SENSOR_PIN 21
#define DHT_SENSOR_TYPE DHT22
int airQuality = 33;
int gasQuality = 35;


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Fios-Lfy8Q";
char pass[] = "eft335non429mug";

BlynkTimer timer;
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
const int sendInt = 50;

WiFiClientSecure client;
void sendSensor() {

  int currTempF = dht.readTemperature(true);
  int currHumidity = dht.readHumidity();
  int air_Qual = digitalRead(airQuality);
  int gas_Quality = digitalRead(gasQuality);
  delay(200);

  Blynk.virtualWrite(V0, currTempF);
  Blynk.virtualWrite(V1, currHumidity);
  Blynk.virtualWrite(V2, air_Qual);
  Blynk.virtualWrite(V3, gas_Quality);
  delay(300);
}

int airQual = 0;
float currTempF = 0.0;
float currHumidity = 0.0;
int gas_Quality = 0;


void setup() {
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);

  currTempF = dht.readTemperature(true);
  currHumidity = dht.readHumidity();
  airQual = analogRead(airQuality);
  gas_Quality = analogRead(gasQuality);
  timer.setInterval(100L, sendSensor);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFI");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(2, LOW);
    delay(2000);
    Serial.print("*");
    digitalWrite(2, HIGH);
    delay(2000);

    Serial.print("Temperature\n");
    Serial.print(currTempF);
    Serial.print("\n");
    Serial.print("Humidity\n");
    Serial.print(currHumidity);
    Serial.print("Air Quality\n");
    Serial.print(airQual);
    Serial.print("GAS Quality\n");
    Serial.print(gas_Quality);
  }
}

void loop() {
  Blynk.run();
  timer.run();
  delay(2000);
  currTempF = dht.readTemperature(true);
  currHumidity = dht.readHumidity();
  airQual = analogRead(airQuality);
  gas_Quality = analogRead(gasQuality);
}
