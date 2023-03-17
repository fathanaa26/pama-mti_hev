const int irPin = 4;
unsigned long duration = 0;
float rpm = 0;
float rpm_a = 0;
int counter = 0;
int present = 0;
int prev = 0;
int state;
unsigned long elapsed = 0;
unsigned long prev_elapsed = 0;

void setup() {
  pinMode(irPin, INPUT);
  elapsed = micros();
  Serial.begin(115200);
  if(digitalRead(irPin) == LOW){
    state = 1;
  }
  if(digitalRead(irPin) == HIGH){
    state = 0;
  }
}

void loop() {
  if (state == 1 && prev == 0) {
    prev = 1;
    duration = elapsed - prev_elapsed;
    prev_elapsed = micros();
  }
  if (state == 1 && prev == 1) {
    prev = 1;
  }
  if (state == 0 && prev == 1) {
    prev = 0;
  }
  if (state == 0 && prev == 0) {
    prev = 0;
    elapsed = micros();
  }

  rpm = 60000000/duration;


  Serial.println("--Serial Debug--");
  // Serial.print("digitalRead(irPin): ");
  // Serial.println(digitalRead(irPin));
  // Serial.print("micros: ");
  // Serial.println(micros());
  // Serial.print("elapsed: ");
  // Serial.println(elapsed);
  // Serial.print("prev_elapsed: ");
  // Serial.println(prev_elapsed);
  // Serial.print("duration: ");
  // Serial.println(duration);
  // Serial.print("duration: in millisecond ");
  // Serial.println(duration/1000);
  Serial.print("rpm: ");
  Serial.println(rpm);
  Serial.println("--Serial Debug End--\n");

}
