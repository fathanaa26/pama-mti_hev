#include<ADS1115_WE.h> 
#include<Wire.h>
#define I2C_ADDRESS 0x48
const float zeroCurrentVoltage_mV = 0.0;

ADS1115_WE adc(I2C_ADDRESS);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  if(!adc.init()){
    Serial.println("ADS1115 not connected!");
  }

  /* Set the voltage range of the ADC to adjust the gain
   * Please note that you must not apply more than VDD + 0.3V to the input pins!
   * 
   * ADS1115_RANGE_6144  ->  +/- 6144 mV
   * ADS1115_RANGE_4096  ->  +/- 4096 mV
   * ADS1115_RANGE_2048  ->  +/- 2048 mV (default)
   * ADS1115_RANGE_1024  ->  +/- 1024 mV
   * ADS1115_RANGE_0512  ->  +/- 512 mV
   * ADS1115_RANGE_0256  ->  +/- 256 mV
   */
  adc.setVoltageRange_mV(ADS1115_RANGE_6144); 

  /* Set the inputs to be compared
   *  
   *  ADS1115_COMP_0_1    ->  compares 0 with 1 (default)
   *  ADS1115_COMP_0_3    ->  compares 0 with 3
   *  ADS1115_COMP_1_3    ->  compares 1 with 3
   *  ADS1115_COMP_2_3    ->  compares 2 with 3
   *  ADS1115_COMP_0_GND  ->  compares 0 with GND
   *  ADS1115_COMP_1_GND  ->  compares 1 with GND
   *  ADS1115_COMP_2_GND  ->  compares 2 with GND
   *  ADS1115_COMP_3_GND  ->  compares 3 with GND
   */
  adc.setCompareChannels(ADS1115_COMP_0_3); 

  Serial.println("ACS712 - Nullstrommessung mit ADS1115");
  Serial.println();
}

void loop() {
  float voltage = 0.0;
  
  for(int i=0; i<10; i++){
    adc.startSingleMeasurement();
    while(adc.isBusy()){}
    voltage += adc.getResult_mV();
  }
  
  voltage /= 10;
  voltage -= zeroCurrentVoltage_mV;
  float current = voltage/0.185;
  Serial.print("ADC712-Spannung [mV]: "); // Voltage
  Serial.print(voltage);
  Serial.print("  /  Strom [mA]: ");  // Current
  Serial.println(current);
  delay(2000);
}