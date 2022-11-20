#include <Arduino.h>

// Pins
#define DATA_PIN 4
#define IRQ_PIN 3

#define LED1_PIN 5
#define LED2_PIN 6
#define LED3_PIN 7
#define LED4_PIN 8
#define LED5_PIN 9
#define LED6_PIN 10

#define PIEZO_PIN 11

// Buzzer
#define CLICK_HERTZ 1000
#define CLICK_DURATION 500
#define BEEP_HERTZ 1000
#define BEEP_DURATION 500

// Constants
const int defaultKeyUp[2] = {0x1b, 0x35};
const byte ledPins[6] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN};
