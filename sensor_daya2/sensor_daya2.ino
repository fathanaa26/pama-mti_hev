#include "header.h"

void setup() {
  Serial.begin(115200);
  ads_init();
  // wifi_init();
  // timeSync(TZ_INFO, "pool.ntp.org");
  // influxClient_init();
  Serial.println("--SETUP END--");
  power_point.addTag("source", "mcu_1");
}

void loop() {

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc3 = ads.readADC_SingleEnded(3);

  for(acsSample; acsSample < 100; acsSample++){
    acsSample = acsSample + adc3;
    delay(3);
  }
  acsAvg = acsSample /100;

  volts3 = adc3 * 0.1875;
  // Serial.print("VAIN3: ");
  // Serial.print(volts3);
  // Serial.println("mV");
  // Serial.print("adc3: ");
  // Serial.println(adc3);
  // Serial.print("acsSample: ");
  // Serial.println(acsSample);
  // Serial.print("acsAvg: ");
  // Serial.println(acsAvg);

  // acsFixVal = (2500 - (acsAvg * volts3) / 185);
  acsFixVal = (acsAvg - 2500)*5/0.185/66;
  Serial.print("acsFixVal: "); //Cyrrent
  Serial.println(acsFixVal);
  Serial.print("mAmps");

  power_point.clearFields();
  power_point.addField("power",volts3);

  Serial.println(power_point.toLineProtocol());
  // influxClient.writePoint(power_point);
  Serial.println(influxClient.getLastErrorMessage());

  loopCounter++;
  Serial.printf("--END OF LOOP #%d--\n",loopCounter);
  delay(1200);

}
