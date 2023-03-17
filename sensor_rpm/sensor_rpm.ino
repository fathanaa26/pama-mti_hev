const int irPin = 4;
volatile int count=0;
int irPin_prev_state;
int irPin_state;

void ICACHE_RAM_ATTR counter()
{
  Serial.println(count++);
  // irPin_state = digitalRead(irPin);
  // if(irPin_state == LOW && irPin_prev_state == HIGH)
  // {
  //   irPin_prev_state == LOW;
  // }
  //  if(irPin_state == HIGH && irPin_prev_state == LOW)
  // {
  //   count++;
  //   irPin_prev_state == HIGH;
  // }
}

void setup(){
  pinMode(irPin, INPUT_PULLUP);
  Serial.begin(9600);

  
  attachInterrupt(
  digitalPinToInterrupt(irPin),
  counter,
  RISING);

}

void loop()
{

}
