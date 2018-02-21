//Code Produced 
//By Mark Edward Landergan
//Science Fair 2013
//Robotic Arm

#include <Servo.h>
#include <EEPROM.h>

#define CALIB_MAX 512
#define CALIB_MIN 100
#define SAMPLE_DELAY 25 // in ms, 50ms seems good

uint8_t recordButtonPin = 6;
uint8_t playButtonPin = 7;
uint8_t servo1Pin = 8;
uint8_t servo2Pin = 9;
uint8_t servo3Pin = 10;
uint8_t servo4Pin = 11;
uint8_t servo5Pin = 12;
uint8_t servo6Pin = 13;
uint8_t servo1FeedbackPin = A0;
uint8_t servo2FeedbackPin = A1;
uint8_t servo3FeedbackPin = A2;
uint8_t servo4FeedbackPin = A3;
uint8_t servo5FeedbackPin = A4;
uint8_t servo6FeedbackPin = A5;
uint8_t ledPin = 3;


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
  
void setup() {
  Serial.begin(9600);
  pinMode(recordButtonPin, INPUT);
  digitalWrite(recordButtonPin, HIGH);
  pinMode(playButtonPin, INPUT);
  digitalWrite(playButtonPin, HIGH);
  pinMode(ledPin, OUTPUT);
  
  Serial.println("Servo RecordPlay");
}

void loop() {
 if (! digitalRead(recordButtonPin)) {
   delay(10);
   // wait for released
   while (! digitalRead(recordButtonPin));
   delay(20);
   // OK released!
   recordAllServos(servo1Pin, servo1FeedbackPin, recordButtonPin);
 }
 
  if (! digitalRead(playButtonPin)) {
   delay(10);
   // wait for released
   while (! digitalRead(playButtonPin));
   delay(20);
   // OK released!
   playAllServo(servo1Pin, playButtonPin);
 }
}

void playAllServo(uint8_t servo1Pin, uint8_t buttonPin) {
  Serial.println("Playing");
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  servo5.attach(servo6Pin);
  while (digitalRead(buttonPin)) {    
  uint8_t x = EEPROM.read(addr);
  Serial.print("Read EE Servo 1: "); Serial.print(x);
    if (x == 255) break;
    // map to 0-180 degrees
    x = map(x1, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
    servo1.write(x);
    addr+++;
    
  uint8_t x = EEPROM.read(addr);
  Serial.print("Read EE Servo 2: "); Serial.print(x);
    if (x == 255) break;
    // map to 0-180 degrees
    x = map(x, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
  servo2.write(x);
    addr+++;  
    
      uint8_t x = EEPROM.read(addr);
  Serial.print("Read EE Servo 3: "); Serial.print(x);
    if (x == 255) break;
    // map to 0-180 degrees
    x = map(x, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
  servo3.write(x);
    addr+++;  
    
  uint8_t x = EEPROM.read(addr);
  Serial.print("Read EE Servo 4: "); Serial.print(x);
    if (x == 255) break;
    // map to 0-180 degrees
    x = map(x, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
  servo4.write(x);
    addr+++;  
    
  uint8_t x = EEPROM.read(addr);
  Serial.print("Read EE Servo 5: "); Serial.print(x);
    if (x == 255) break;
    // map to 0-180 degrees
    x = map(x, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
  servo5.write(x);
    addr+++;  
    
  uint8_t x = EEPROM.read(addr);
  Serial.print("Read EE Servo 6: "); Serial.print(x);
    if (x == 255) break;
    // map to 0-180 degrees
    x = map(x, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
  servo6.write(x);
    addr+++;  
    
  }
  Serial.println("Done");
  servo1.detach();
  delay(250);  
}

void recordAllServos(uint8_t servo1Pin, uint8_t servo1FeedbackPin, uint8_t buttonPin) {
  uint16_t addr = 0;
  
  Serial.println("Recording");
  digitalWrite(ledPin, HIGH);
 
  pinMode(servo1FeedbackPin, INPUT); 
  pinMode(servo2FeedbackPin, INPUT); 
  pinMode(servo3FeedbackPin, INPUT); 
  pinMode(servo4FeedbackPin, INPUT); 
  pinMode(servo5FeedbackPin, INPUT); 
  pinMode(servo6FeedbackPin, INPUT); 

  while (digitalRead(buttonPin)) 
  {
     readAllServo(servo1FeedbackPin);
     readAllServo(servo2FeedbackPin);
     readAllServo(servo3FeedbackPin);
     readAllServo(servo4FeedbackPin);
     readAllServo(servo5FeedbackPin);
     readAllServo(servo6FeedbackPin);
    if (addr == 1024) break;
    delay(SAMPLE_DELAY);
  }
  if (addr != 1024) EEPROM.write(addr, 255);
  digitalWrite(ledPin, LOW);
  
  Serial.println("Done");
  delay(250);
}

void readAllServo(uint8_t servo1FeedbackPin)
{
     
     uint16_t a = analogRead(servo1FeedbackPin); 
     Serial.print("Read analog pin "); Serial.print(servo1FeedbackPin); Serial.print(": "); Serial.print(a);
     if (a < CALIB_MIN) a = CALIB_MIN;
     if (a > CALIB_MAX) a = CALIB_MAX;
     a = map(a, CALIB_MIN, CALIB_MAX, 0, 254);
     Serial.print(" -> "); Serial.println(a);
     EEPROM.write(addr, a); //save servo 1 values to eeprom
     addr++
}
