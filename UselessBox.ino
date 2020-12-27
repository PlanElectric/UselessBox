#include <FastLED.h>
#include <Servo.h>

// How many LEDs in your strip
#define NUM_LEDS 7
// Ws2812B LED data PIN
#define DATA_PIN 4
// Arduino pin for Servo opening Box lid
#define SERVO_LID_PIN 3
// Opened position of Box lid
#define SERVO_LID_OPENED 120
// Closed position of lid
#define SERVO_LID_CLOSED 65
// Arduino pin for arm servo
#define SERVO_ARM_PIN 5
// Hidden arm position
#define SERVO_ARM_HIDED 20
// Pressed switch position
#define SERVO_ARM_PRESSED 160
// Arduino pin for toggle swtich
#define SWITCH_PIN 2


// Define the array of LEDs
CRGB leds[NUM_LEDS];
Servo servoLid;  // create servo object to control a lid servo
Servo servoArm;  // create servo object to control an arm servo
int servoArmPos = 0;  // variable to store the servo position
int servoLidPos = 0;  // variable to store the servo position
int switchState = 0;  // variable to store the servo position
int sequenceNum = 0;  // variable to store the servo position

void setup() {

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  ledsOff();  // Turn all LED's off
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Set toggle switch as input
  servoLid.detach(); // Must be detached at the begging but after LED's init
  servoArm.detach(); // Must be detached at the begging but after LED'S init
  servoArm.write(SERVO_ARM_HIDED); // Write default position
  servoLid.write(SERVO_LID_CLOSED); // Write default position
  servoArm.attach(SERVO_ARM_PIN); // Attach and move servo arm
  delay(1000); // Wait till servo arm completed move
  servoLid.attach(SERVO_LID_PIN);  // Attaches signal to lid servo
  
}

void loop() {

  // Read state of toggle switch
  switchState = digitalRead(SWITCH_PIN);

  // If switch was toggled
  if (!switchState)
  {
    sequenceNum++;
    if (sequenceNum > 8)
      sequenceNum = 1;

    // Sequential animations
    switch (sequenceNum)
    {
      case 1:
        sequence_8();
        break;
      case 2:
        sequence_2();
        break;
      case 3:
        sequence_1();
        break;
      case 4:
        sequence_3();
        break;
      case 5:
        sequence_5();
        break;
      case 6:
        sequence_4();
        break;
      case 7:
        sequence_6();
        break;
      case 8:
        sequence_7();
        break;
    }
  }
  delay(10);
}

// Animations 

// Open, quick press, quick hide, close
void sequence_2() {
  ledsOn();
  openLidSlowly();
  delay(100);
  pressFast();
  ledsOff();
  hideFast();
  closeLidSlowlyFaster();
}

void sequence_1() {
  ledsOn();
  openLidSlowly();
  pressSlowlyAlmost();
  delay(200);
  closeLidAlmostSlowly();
  delay(3000);
  openLidSlowly();
  delay(100);
  pressFastShort();
  ledsOff();
  hideFast();
  closeLidSlowlyFaster();
}

void sequence_3() {
  ledsOn();
  openLidSlowly();
  pressSlowly();
  ledsOff();
  hideSlowly();
  closeLidSlowly();
  delay(1000);
  openLidAlmostSlowly();
  delay(1000);
  closeLidSlowly();
}

void sequence_8() {
  ledsOn();
  openLidSlowly();
  pressSlowly();
  ledsOff();
  hideSlowly();
  closeLidSlowly();
}

void sequence_4() {
  ledsOn();
  openLidAlmostSlowly();
  delay(1000);
  closeLidFast();
  delay(4000);
  openLidSlowly();
  delay(100);
  pressFast();
  ledsOff();
  hideFast();
  closeLidSlowlyFaster();
}

void sequence_5()
{
  ledsOn();
  openLidSlowly();
  delay(100);
  pressMadness();
  ledsOff();
  hideFast();
  closeLidSlowlyFaster();
}

void sequence_6() {
  ledsOn();
  lidMadness();
  openLidFast();
  pressFast();
  ledsOff();
  hideFast();
  delay(200);
  closeLidSlowlyFaster();
}

void sequence_7() {
  ledsOn();
  openLidSlowly();
  delay(1000);
  closeLidSlowly();
  delay(3000);
  openLidSlowly();
  pressSlowlyAlmost();
  pressFastShort();
  ledsOff();
  hideSlowly();
  closeLidSlowly();
}

// Functions which help to create animations

void openLidFast()
{
  servoLid.write(SERVO_LID_OPENED);
  delay(200);
}

void closeLidFast()
{
  servoLid.write(SERVO_LID_CLOSED);
  delay(200);
}

void openLidSlowly()
{
  int actualPos = servoLid.read();
  for (int pos = actualPos; pos < SERVO_LID_OPENED; pos++)
  {
    servoLid.write(pos);
    delay(10);
  }
}

void closeLidSlowly()
{
  int actualPos = servoLid.read();
  for (int pos = actualPos; pos > SERVO_LID_CLOSED; pos--)
  {
    servoLid.write(pos);
    delay(10);
  }
}

void closeLidSlowlyFaster()
{
  int actualPos = servoLid.read();
  for (int pos = actualPos; pos > SERVO_LID_CLOSED; pos--)
  {
    servoLid.write(pos);
    delay(5);
  }
}

void closeLidAlmostSlowly()
{
  int actualPos = servoLid.read();
  for (int pos = actualPos; pos > SERVO_LID_CLOSED + 18; pos--)
  {
    servoLid.write(pos);
    delay(20);
  }
}

void openLidAlmostSlowly()
{
  int actualPos = servoLid.read();
  for (int pos = actualPos; pos < SERVO_LID_OPENED - 12; pos++)
  {
    servoLid.write(pos);
    delay(15);
  }
}
void openLidAlmostFast()
{
  servoLid.write(SERVO_LID_OPENED - 12);
  delay(200);
}

void pressFast()
{
  servoArm.write(SERVO_ARM_PRESSED);
  delay(400);
}

void pressFastShort()
{
  servoArm.write(SERVO_ARM_PRESSED);
  delay(80);
}

void pressMadness()
{
  servoArm.write(SERVO_ARM_PRESSED - 20);
  delay(300);
  servoArm.write(SERVO_ARM_PRESSED - 60);
  delay(200);
  servoArm.write(SERVO_ARM_PRESSED - 20);
  delay(200);
  servoArm.write(SERVO_ARM_PRESSED - 60);
  delay(200);
  servoArm.write(SERVO_ARM_PRESSED);
  delay(200);
}

void lidMadness()
{
  openLidAlmostFast();
  closeLidFast();
  openLidAlmostFast();
  closeLidFast();
  openLidAlmostFast();
  closeLidFast();
  openLidAlmostFast();
  closeLidFast();
}

void pressSlowly()
{
  int actualPos = servoArm.read();
  for (int pos = actualPos; pos < SERVO_ARM_PRESSED - 10; pos++)
  {
    servoArm.write(pos);
    delay(15);
  }
  servoArm.write(SERVO_ARM_PRESSED);
  delay(80);
}

void pressSlowlyAlmost()
{
  int actualPos = servoArm.read();
  for (int pos = actualPos; pos < SERVO_ARM_PRESSED - 10; pos++)
  {
    servoArm.write(pos);
    delay(15);
  }
}

void pressFastAlmost()
{
  servoArm.write(SERVO_ARM_PRESSED - 10);
  delay(300);
}

void hideFast()
{
  servoArm.write(SERVO_ARM_HIDED);
  delay(400);
}

void hideSlowly()
{
  int actualPos = servoArm.read();
  for (int pos = actualPos; pos > SERVO_ARM_HIDED; pos--)
  {
    servoArm.write(pos);
    delay(15);
  }
}

void ledsOff()
{
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;

  servoLid.detach();   // PWM servo control must be disabled or servo will jitter - problem with interrupts descrived in FastLED library
  servoArm.detach();
  FastLED.show();
  servoLid.attach(SERVO_LID_PIN);
  servoArm.attach(SERVO_ARM_PIN);

}

void ledsOn()
{
  CHSV color = CHSV(random8(), 255, 255);
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = color;

  servoLid.detach();   // PWM servo control must be disabled or servo will jitter - problem with interrupts descrived in FastLED library
  servoArm.detach();     
  FastLED.show();
  servoLid.attach(SERVO_LID_PIN);
  servoArm.attach(SERVO_ARM_PIN);
}
