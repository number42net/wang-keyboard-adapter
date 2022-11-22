#include <Arduino.h>

// Pins
#define DATA_PIN 4
#define IRQ_PIN 3

#define LED1_PIN 31
#define LED2_PIN 33
#define LED3_PIN 35
#define LED4_PIN 37
#define LED5_PIN 39
#define LED6_PIN 53

#define PIEZO_PIN 7

// Buzzer
#define CLICK_HERTZ 5000
#define CLICK_DURATION 10
#define BEEP_HERTZ 1700
#define BEEP_DURATION 60

// Constants
const int defaultKeyUp[2] = {0x1b, 0x35};
const byte ledPins[6] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN};
