#include <Arduino.h>
#include <PS2Keyboard.h>
#include "scanconvert.h"
#include "config.h"

PS2Keyboard keyboard;

int customKeyUp[5];
bool allKeyUp;
int ledState;
int volumeState;
uint8_t lastScanCode;

void setup()
{
    Serial2.begin(115200);
    Serial1.begin(62500);

    keyboard.begin(DATA_PIN, IRQ_PIN);

    for (int x = 0; x < 6; x++)
    {
        pinMode(x, OUTPUT);
    }
    pinMode(PIEZO_PIN, OUTPUT);

    Serial2.println("Starting Wang keyboard converter");
}

void updateLeds()
{
    for (int x = 0; x < 6; x++)
    {
        if (ledState & (1 << x))
        {
            digitalWrite(ledPins[x], HIGH);
        }
        else
        {
            digitalWrite(ledPins[x], LOW);
        }
    }
}

uint8_t getMoreScanCodes()
{
    for (int i = 0; i < 10; i++)
    {
        if (keyboard.available())
        {
            return keyboard.readScanCode();
        }
        else
        {
            delay(100);
        }
    }
    return 0;
}

void processCommand()
{
    int data = Serial1.read();
    switch (data)
    {
    case 0x00:
        Serial2.println("No-op");
        break;
    case 0x01:
        Serial2.println("Key-up config with 1 parameter");
        // Apply new parameters
        for (int x = 0; x < 1; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 1; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x02:
        Serial2.println("Key-up config with 2 parameter");
        // Apply new parameters
        for (int x = 0; x < 2; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 2; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x03:
        Serial2.println("Key-up config with 3 parameter");
        // Apply new parameters
        for (int x = 0; x < 3; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 3; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x04:
        Serial2.println("Key-up config with 4 parameter");
        // Apply new parameters
        for (int x = 0; x < 4; x++)
        {
            customKeyUp[x] = getMoreScanCodes();
        }
        // Reset the others
        for (int x = 4; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x05:
        Serial2.println("Key-up config with 5 parameter");
        // Reset the others
        for (int x = 5; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x06:
        Serial2.println("Key-up config - All keys");
        for (int x = 0; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = true;
        break;
    case 0x07:
        Serial2.println("Key-up config - Default (only shift)");
        for (int x = 0; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        break;
    case 0x08:
        Serial2.println("Reset");
        for (int x = 0; x < 5; x++)
        {
            customKeyUp[x] = 0;
        }
        allKeyUp = false;
        ledState = 0;
        volumeState = 0;
        lastScanCode = 0;
        updateLeds();
        break;
    case 0x09:
        Serial2.println("Keyboard ID");
        Serial1.write(0x01);
        Serial1.write(0x33);
        break;
    case 0x0A:
        Serial2.println("Key click");
        tone(PIEZO_PIN, CLICK_HERTZ, CLICK_HERTZ);
        break;
    case 0x0B:
        Serial2.println("Beep");
        tone(PIEZO_PIN, BEEP_HERTZ, BEEP_HERTZ);
        break;
    case 0x0C:
        Serial2.println("Repeat last scancode sent");
        Serial1.write(lastScanCode);
        break;
    case 0x0E:
        Serial2.println("Return status of DIP switches - Not yet implemented");
        // TODO
        break;
    case 0x0F:
        Serial2.println("Return beeper / keyclick volume");
        Serial1.write(0x01);
        Serial1.write(volumeState);
        break;
    case 0x10:
        Serial2.println("Turn on LED 1 (Lock key)");
        ledState |= (1 << 0);
        updateLeds();
        break;
    case 0x11:
        Serial2.println("Turn off LED 1");
        ledState &= ~(1 << 0);
        updateLeds();
        break;
    case 0x12:
        Serial2.println("Turn on LED 2");
        ledState |= (1 << 1);
        updateLeds();
        break;
    case 0x13:
        Serial2.println("Turn off LED 2");
        ledState &= ~(1 << 1);
        updateLeds();
        break;
    case 0x14:
        Serial2.println("Turn on LED 3");
        ledState |= (1 << 2);
        updateLeds();
        break;
    case 0x15:
        Serial2.println("Turn off LED 3");
        ledState &= ~(1 << 2);
        updateLeds();
        break;
    case 0x16:
        Serial2.println("Turn on LED 4");
        ledState |= (1 << 3);
        updateLeds();
        break;
    case 0x17:
        Serial2.println("Turn off LED 4");
        ledState &= ~(1 << 3);
        updateLeds();
        break;
    case 0x18:
        Serial2.println("Turn on LED 5");
        ledState |= (1 << 4);
        updateLeds();
        break;
    case 0x19:
        Serial2.println("Turn off LED 5");
        ledState &= ~(1 << 4);
        updateLeds();
        break;
    case 0x1A:
        Serial2.println("Turn on LED 6");
        ledState |= (1 << 5);
        updateLeds();
        break;
    case 0x1B:
        Serial2.println("Turn off LED 6");
        ledState &= ~(1 << 5);
        updateLeds();
        break;
    case 0x1C:
        Serial2.println("Turn on all LEDs");
        ledState = 0b00111111;
        updateLeds();
        break;
    case 0x1D:
        Serial2.println("Turn off all LEDs");
        updateLeds();
        ledState = 0;
        break;
    case 0x1E:
        Serial2.println("Get LED status");
        Serial1.write(0x01);
        Serial1.write(ledState);
        break;
    case 0x20:
        Serial2.println("Set beeper / keyclick volume");
        volumeState = getMoreScanCodes();
        getMoreScanCodes();
        break;
    case 0x31:
        Serial2.println("Program the sound generator - Not implemented");
        getMoreScanCodes();
        // TODO
        break;
    case 0x32:
        Serial2.println("Program the sound generator - Not implemented");
        getMoreScanCodes();
        getMoreScanCodes();
        // TODO
        break;
    default:
        Serial2.print("Unknown command: ");
        Serial2.println(data, HEX);
    }
}

void processScanCode()
{
    // Read the scan code
    unsigned int PS2scanCode = keyboard.readScanCode();
    switch (PS2scanCode)
    {
    case 0:
        // Don't do anything if the value is zero
        return;

    case 0xF0:
        // Key up code, try to fetch the 2nd part and ignore it
        getMoreScanCodes();
        return;

    case 0xE0:
        // 16 bit scan code, try to fetch the 2nd part and combine them
        uint8_t more = getMoreScanCodes();

        // Ignore key-up events for now
        if (more == 0xF0)
        {
            getMoreScanCodes();
            getMoreScanCodes();
            return;
        }

        PS2scanCode = word(0xE0, more);
    }

    // Attempt to convert the scan code
    uint8_t wangScanCode = convertScanCode(PS2scanCode);
    if (wangScanCode)
    {
        Serial2.print("Converted PS/2 scan code: ");
        Serial2.print(PS2scanCode, HEX);
        Serial2.print(" to Wang scan code: ");
        Serial2.println(wangScanCode, HEX);
        // Sent to Wang if successful:
        Serial1.write(wangScanCode);
        lastScanCode = wangScanCode;
    }
    else
    {
        Serial2.print("Could not convert PS/2 scan code: ");
        Serial2.println(PS2scanCode, HEX);
    }
}

void loop()
{
    // Check if any commands from the Wang need to be processed
    if (Serial1.available())
    {
        processCommand();
    }
    // Check if any keyboard scan codes are available
    if (keyboard.available())
    {
        processScanCode();
    }
}
