#include "init.h"

void setup() {
  Serial.begin(115200);

  Serial.println("Set Gain 2/3");
  ads.setGain(GAIN_TWOTHIRDS);
  if(!ads.begin()){
    Serial.println("[ERR] ADS1115 Failed to begin");
  }
  // Setup wifi
  WiFi.mode(WIFI_STA);
  Serial.println("WiFi Mode Station");
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Connected to WiFi");
  Serial.printf("SSID: %s, IP: %d \n",WIFI_SSID,WiFi.localIP());

  // Add tags
  current_point.addTag("device_id", "mcu_1");
  voltage_point.addTag("device_id", "mcu_1");
  power_point.addTag("device_id", "mcu_1");

  // Accurate time is necessary for certificate validation and writing in batches
  // For the fastest time sync find NTP servers in your area: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (influxClient.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(influxClient.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(influxClient.getLastErrorMessage());
  }

  Serial.println();
}

float adc_v;
float in_v;

float r1 = 200000.0; //ohm
float r2 = 10000.0; //ohm

// floar vref = 2.5;

void loop() {

  // Clear fields for reusing the point. Tags will remain untouched
    current_point.clearFields();
    voltage_point.clearFields();
    power_point.clearFields();
    
    adc0 = ads.readADC_SingleEnded(0) * -1;
    adc1 = ads.readADC_SingleEnded(1) * -1;
    adc3 = ads.readADC_SingleEnded(3) * -1;

    // v_adc0 = (adc0 * 1875)/10000;
    // v_adc1 = (adc1 * 1875)/10000;
    // v_adc3 = (adc3 * 1875)/10000;

    Serial.println(adc3);
    Serial.println(adc0);
    Serial.println(adc1);
    
    // Store measured value into point
    // Report RSSI of currently connected network
    current_point.addField("current", random(10,13));
    voltage_point.addField("voltage", random(14,16));
    power_point.addField("power", random(17,19));

    // Print what are we exactly writing
    Serial.println("Writing: ");
    Serial.println(current_point.toLineProtocol());
    Serial.println(voltage_point.toLineProtocol());
    Serial.println(power_point.toLineProtocol());
    Serial.println("Writing End \n ");


    if (!influxClient.writePoint(current_point)) {
        Serial.print("InfluxDB write failed: ");
        Serial.println(influxClient.getLastErrorMessage());
      }
    if (!influxClient.writePoint(voltage_point)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(influxClient.getLastErrorMessage());
    }
    if (!influxClient.writePoint(power_point)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(influxClient.getLastErrorMessage());
    }

 

  // Check WiFi connection and reconnect if needed
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }

  delay(2000);
}
