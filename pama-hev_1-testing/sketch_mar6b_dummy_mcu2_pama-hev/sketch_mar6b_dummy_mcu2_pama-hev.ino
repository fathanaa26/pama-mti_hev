#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message{
  int id;
  int rpm;
  int ac_current;
  int voltage;
} struct_message;

struct_message dataPayload;

uint8_t bcAddr_mcu [] = {0x7C, 0x9E, 0xBD, 0x45, 0xA5, 0xEC};

unsigned long _100ms_millis = 1500;
unsigned long prev_100ms_millis = 0;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStat){
  Serial.println("");
  Serial.println("Last Packet Payload Send Status: ");
  if(sendStat == 0){
    Serial.println("Packet Payload Delivery Success");
  }else{
    Serial.println("Packet Payload Delivery Fail");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  WiFi.disconnect();

  if(esp_now_init() != 0){  
    Serial.println("Error init. ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(bcAddr_mcu, ESP_NOW_ROLE_SLAVE,1,NULL,0);

  
}

void loop() {
  
  for(int x = 700; x < 4500; x++){
      if((millis() - prev_100ms_millis) > _100ms_millis){
      dataPayload.id = 2;
      dataPayload.rpm = x;
      Serial.println(x);
      esp_now_send(0, (uint8_t *) &dataPayload, sizeof(dataPayload));
    
      prev_100ms_millis = millis();
    }    
  }
}
