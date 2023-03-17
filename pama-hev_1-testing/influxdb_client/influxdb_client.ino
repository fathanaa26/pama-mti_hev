
#include <WiFi.h>
#define DEVICE "ESP32"
#include <esp_now.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define WIFI_SSID "PDP Atas"
#define WIFI_PASSWORD "kumahaaa"
#define INFLUXDB_URL "http://10.133.226.142:8086"
#define INFLUXDB_TOKEN "RBPu6c8YH8M5C0lDFZGPDLyfIsD9HKgWyxMcKEAnqvOVpVqYWXm7r9BJgP2JjAdojbwQBDKDn4sRv5UVGKRMtA=="
#define INFLUXDB_ORG "PAMA PUCB"
#define INFLUXDB_BUCKET "hev-testing"

#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);


typedef struct struct_message {
  int id;
  int rpm;
  int ac_current;
  int voltage;
} struct_message;

struct_message dataPayload;
struct_message mcu_1;
struct_message mcu_2;

struct_message mcuStruct[2] = {
  mcu_1, mcu_2
};

Point sensor_ac("sensor_ac");
Point sensor_v("sensor_v");
Point sensor_rpm("sensor_rpm");

void setup() {
  Serial.begin(115200);
  WiFiBegin();
  espnow_init();
  esp_now_register_recv_cb(OnDataRecv);
  ntp();

  sensor_ac.addTag("mcu", "mcu1");
  sensor_v.addTag("mcu", "mcu1");
  sensor_rpm.addTag("mcu", "mcu2");

  influxdb_init();
}

void loop() {

  sensor_ac.clearFields();
  sensor_v.clearFields();
  sensor_rpm.clearFields();

  sensor_ac.addField("AC Current", dataPayload.ac_current);/*dataPayload.ac_current*/ //dummy_res(10,20)
  sensor_v.addField("Voltage", dataPayload.voltage);/*dataPayload.voltage*/ //dummy_res(20,30)
  sensor_rpm.addField("rpm", dataPayload.rpm);/*dataPayload.rpm*/

  sensor_ac.toLineProtocol();
  sensor_v.toLineProtocol();
  sensor_rpm.toLineProtocol();

  if (!client.writePoint(sensor_ac)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  if (!client.writePoint(sensor_v)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  if (!client.writePoint(sensor_rpm)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

}
