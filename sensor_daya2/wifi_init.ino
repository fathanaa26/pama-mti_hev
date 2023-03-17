void wifi_init(){
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Connected to WiFi");
  Serial.printf("SSID: %s",WIFI_SSID);
}