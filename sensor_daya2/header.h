// Microcontroller Initiation 
#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

unsigned long loopCounter = 0;

#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;
int16_t adc0, adc1, adc2, adc3;
float volts0, volts1, volts2, volts3;

float acsSample = 0.0;
float acsAvg = 0.0;
float acsFixVal = 0.0;

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#define WIFI_SSID "PDP Atas"
#define WIFI_PASSWORD "kumahaaa"
#define INFLUXDB_URL "http://10.133.226.146:8086"
#define INFLUXDB_TOKEN "oup7XI98_nVYXJ3xSMR8ME16EaOBdBb8Vy8PNPeCBw9UsRW2XEULjuePKMoPBvOFkHvh45zP3_ib_MtfDOV1-g=="
#define INFLUXDB_ORG "pama-pucb"
#define INFLUXDB_BUCKET "hev"

// Set timezone string according to https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
// Examples:
//  Pacific Time: "PST8PDT"
//  Eastern: "EST5EDT"
//  Japanesse: "JST-9"
//  Central Europe: "CET-1CEST,M3.5.0,M10.5.0/3"
#define TZ_INFO "UTC+7"

InfluxDBClient influxClient(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Point current_point("current_sensor");
// Point voltage_point("voltage_sensor");
Point power_point("power_calc");
