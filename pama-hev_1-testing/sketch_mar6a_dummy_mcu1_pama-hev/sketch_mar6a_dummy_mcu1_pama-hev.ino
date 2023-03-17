#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

typedef struct struct_message{
  int id;
  int rpm;
  int ac_current;
  int voltage;
} struct_message;

struct_message dataPayload;

uint8_t bcAddr_mcu [] = {0x7C, 0x9E, 0xBD, 0x45, 0xA5, 0xEC};

unsigned long _100ms_millis = 1000;
unsigned long prev_100ms_millis = 0;

constexpr char WIFI_SSID[] = "PDP Atas";

void setup() {
  Serial.begin(115200);
  WiFiBegin();
  espnow_init();
  esp_now_register_send_cb(OnDataSent);
  
}

void loop() {
  
  if((millis() - prev_100ms_millis) > _100ms_millis){
    dataPayload.id = 1;
    dataPayload.voltage = random(210,235);
    dataPayload.ac_current = random(0,10);

    Serial.printf("AC Current %d \n", dataPayload.ac_current);
    Serial.printf("Voltage %d \n", dataPayload.voltage);

    esp_now_send(NULL, (uint8_t *) &dataPayload, sizeof(dataPayload));

    prev_100ms_millis = millis();
  }

}
