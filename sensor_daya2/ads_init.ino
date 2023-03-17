
void ads_init(){
  ads.setGain(GAIN_TWOTHIRDS);
  if(!ads.begin()){
    Serial.println("ADS FAILED TO BEGIN");
  }
}