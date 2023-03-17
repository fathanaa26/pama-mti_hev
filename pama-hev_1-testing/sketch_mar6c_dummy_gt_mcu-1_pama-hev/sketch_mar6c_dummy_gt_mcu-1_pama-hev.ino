
#include <WiFi.h>
#include <esp_now.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

int a;
int b;
int c;

typedef struct struct_message{
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

#define WIFI_SSID "PDP Atas"
#define WIFI_PASSWORD "kumahaaa"

void OnDataRecv(
  const uint8_t *mac_addr, 
  const uint8_t *incomingPayload,
  const int len){
  
  memcpy(&dataPayload, incomingPayload, sizeof(dataPayload));
  
  mcuStruct[dataPayload.id-1].ac_current = dataPayload.ac_current;
  mcuStruct[dataPayload.id-1].voltage = dataPayload.voltage;
  mcuStruct[dataPayload.id-1].rpm = dataPayload.rpm;

  printf("AC: %d \n V: %d \n RPM: %d \n",
  dataPayload.ac_current,
  dataPayload.voltage,
  dataPayload.rpm);
  
}
 
unsigned long prev_100ms = 0;

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to wifi");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
    }
  Serial.println();

  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }else{
    Serial.println("Success initializing ESP-NOW");
  }

  esp_now_register_recv_cb(OnDataRecv);
  
  
}


void loop() {

}
