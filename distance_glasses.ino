/*
 */

  const int BUZZER = 2;
  const int ECHO = 10;
  const int TRIG = 9;

  float distance = 0;
  int currentZone = 0, lastZone = 0, timer = 0;
  double lastBuzzerTime;

  //the far bound of each zone. these can be easily adjusted by the end user to customize their experience.
  int zones[5] = {150, 75, 50, 25, 10};
  //the timer for how often the buzzer sounds. this can also be adjusted by the end user
  int zoneTimers[6] = {2000, 1000, 750, 500, 250, 100};


void setup() {

    pinMode(BUZZER, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    Serial.begin(9600);

  lastBuzzerTime = millis();
  
}

/* The basic logic is that when the distance is measured by the ultrasonic sensor, it's catergorized into a zone, with higher numbers being closer
  each zone has an associated "timer" value that denotes the length of time between buzzer activations
  in order to not be blocked by delay() code, we check the difference between the current time with millis() and last recorded buzzer time
  if the difference in time is greater than the timeout timer, sound the buzzer and update the most recent buzzer time
*/

void loop() {

    delay(100);
  
    readDistance();

    if(distance > zone[0]) {
      currentZone = 0;
    } else if(distance > zones[1] && distance < zones[0]) {
      currentZone = 1;
    } else if(distance > zones[2] && distance < zones[1]) {
      currentZone = 2;
    } else if(distance > zones[3] && distance < zones[2]) {
      currentZone = 3;
    } else if (distance > zones[4] && distance < zones[3]) {
        currentZone = 4;
    } else {
      currentZone = 5;
    }

  timer = zoneTimers[currentZone];
  
  if(millis() - lastBuzzerTime > timer) {
    soundBuzzer();
  }
  
  if(currentZone != lastZone) {
    lastZone = currentZone;
  }
    
    
}

void readDistance() {
    digitalWrite(TRIG, LOW);
    delay(2);
    digitalWrite(TRIG, HIGH);
    delay(2);
    digitalWrite(TRIG, LOW);
    distance = pulseIn(ECHO, HIGH) / 58.0;
//    Serial.print(distance);
//    Serial.print("\n");
}

void soundBuzzer() {
  tone(BUZZER, 300);
  delay(50);
  noTone(BUZZER);
  lastBuzzerTime = millis();
}
