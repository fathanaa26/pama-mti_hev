#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define WIFI_SSID "PDP Atas"
#define WIFI_PASSWORD "kumahaaa"
#define INFLUXDB_URL "http://10.133.226.142:8086"
#define INFLUXDB_TOKEN "ZgXWSc6UtIb8KJOMXbWNP63l1DqazZMbLafSvY9CbGV92urbZmvr0bD-jlv9k4G7vh8FB4zOWtQemcbBT5tuuQ=="
#define INFLUXDB_ORG "pama-pucb"
#define INFLUXDB_BUCKET "hev"


#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

Point rpm("rpm");

unsigned long _1000ms_millis = 0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {

  rpm.clearFields();

  rpm.addField("rpm", random(3400,3600));

  if((millis() - _1000ms_millis) > 1000){
    Serial.print("Writing: ");
    Serial.println(rpm.toLineProtocol());
    _1000ms_millis = millis();
  }

  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }

  if (!client.writePoint(rpm)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  Serial.println("Wait 1s");
  delay(1000);
}

